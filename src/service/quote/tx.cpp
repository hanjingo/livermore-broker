#include "tx.h"
#include "market_data_shm.h"

#include <libcpp/log/logger.hpp>
#include <libcpp/net/http/http_client.hpp>
#include <libcpp/util/string_util.hpp>
#include <libcpp/encoding/bytes.hpp>

namespace quote
{

tx::tx()
{

}

tx::~tx()
{
    for (auto itr = _m_md.begin(); itr != _m_md.end(); ++itr)
    {
        delete itr->second;
        itr->second = nullptr;
    }
}

error tx::init()
{
    register_cb();

    return error::ok;
}

error tx::subscribe_market_data(const std::vector<std::string>& instruments)
{
    for (int i = 0; i < instruments.size(); ++i)
    {
        if (_m_md.find(instruments[i]) != _m_md.end())
            continue;

        _m_md.emplace(instruments[i], new common::market_data_shm(instruments[i]));
        _addr.append(",");
        _addr.append(instruments[i]);
        LOG_DEBUG("sub topic={}", instruments[i]);
    }

    LOG_DEBUG("subscribe_market_data succ with _addr={}", _addr);
    return error::ok;
}

error tx::unsubscribe_market_data(const std::vector<std::string>& instruments)
{
    for (int i = 0; i < instruments.size(); ++i)
    {
        if (_m_md.find(instruments[i]) == _m_md.end())
            continue;

        delete _m_md[instruments[i]];
        _m_md[instruments[i]] = nullptr;
        _m_md.erase(instruments[i]);
        LOG_DEBUG("unsub topic={}", instruments[i]);
    }

    // reset _addr
    _addr = "/q=";
    for (auto itr = _m_md.begin(); itr != _m_md.end(); ++itr)
    {
        _addr.append(",");
        _addr.append(itr->first);
    }

    return error::ok;
}

error tx::wait(int ms)
{
    std::chrono::milliseconds interval{1};
    while(ms > 0 || ms == -1)
    {
        _query_md();
        std::this_thread::sleep_for(interval);
        ms = (ms > 0 ? ms - 1 : ms);
    }

    return error::ok;
}

error tx::_query_md(int ms)
{
    libcpp::http_client cli{_tx_addr_base};
    auto resp = cli.Get(_addr);
    LOG_TRACE("_query_md with body: {}", resp->body);
    auto instruments = libcpp::string_util::split(resp->body, ";");
    std::vector<common::market_data_shm*> mds;
    std::string id;
    for (std::string str : instruments)
    {
        id = _parse_id(str);
        auto itr = _m_md.find(id);
        if(itr == _m_md.end())
            continue;

        if(!_parse_md(str, itr->second))
            continue;

        mds.push_back(itr->second);
    }
    _on_md_ntf(mds);
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    return error::ok;
}

std::string tx::_parse_id(const std::string& body)
{
    std::smatch match;
    // libcpp::string_util::search(body, match, R"_(\_([^=]+)=)_");
    std::regex pattern(R"_(\_([^=]+)=)_");
    std::regex_search(body, match, pattern);
    return match[1];
}

bool tx::_parse_md(const std::string& body, common::market_data_shm* md)
{
    // 0:, 1:instrument_name, 2:instrument_id, 3:last_price, 4:pre_close_price, 5:open_price, 6:volume, 7:, 8:,
    // 9:bid_price1, 10:bid_volumn1, 11:bid_price2, 12:bid_volumn2, 13:bid_price3, 14:bid_volumn3, 
    // 15:bid_price4, 16:bid_volumn4, 17:bid_price5, 18:bid_volumn5, 19:ask_price1, 20:ask_volumn1, 
    // 21:ask_price2, 22:ask_volumn2, 23:ask_price3, 24:ask_volumn3, 25:ask_price4, 26:ask_volumn4, 
    // 27:ask_price5, 28:ask_volumn5, 29:, 30:trading_day, 31, 32, 33:highest_price, 34:lowest_price,
    // 35:, 36:settlement_price(10K)
    md->reset();
    auto params = libcpp::string_util::split(body, "~");
    if (params.size() < 38)
        return false;
    for (auto itr = params.begin(); itr != params.end(); ++itr)
    {
        *itr = std::regex_replace(*itr, std::regex("~"), "");
    }

    std::smatch match;
    std::regex pattern(R"(v_([a-zA-Z]+)[0-9])");
    std::regex_search(params[0], match, pattern);
    libcpp::string_to_bytes(std::string(match[1]), md->data->exchange_id); 

    libcpp::string_to_bytes(params[1], md->data->instrument_name);
    libcpp::string_to_bytes(params[2], md->data->instrument_id);
    md->data->last_price       = std::stod(params[3]);
    md->data->pre_close_price  = std::stod(params[4]);
    md->data->open_price       = std::stod(params[5]);
    md->data->volume           = std::stod(params[6]) * 100.0;

#ifdef DEPTH_MARKET_DATA
    md->data->bid_price1       = std::stod(params[9]);
    md->data->bid_volumn1      = std::stod(params[10]);
    md->data->bid_price2       = std::stod(params[11]);
    md->data->bid_volumn2      = std::stod(params[12]);
    md->data->bid_price3       = std::stod(params[13]);
    md->data->bid_volumn3      = std::stod(params[14]);
    md->data->bid_price4       = std::stod(params[15]);
    md->data->bid_volumn4      = std::stod(params[16]);
    md->data->bid_price5       = std::stod(params[17]);
    md->data->bid_volumn5      = std::stod(params[18]);
    md->data->ask_price1       = std::stod(params[19]);
    md->data->ask_volumn1      = std::stod(params[20]);
    md->data->ask_price2       = std::stod(params[21]);
    md->data->ask_volumn2      = std::stod(params[22]);
    md->data->ask_price3       = std::stod(params[23]);
    md->data->ask_volumn3      = std::stod(params[24]);
    md->data->ask_price4       = std::stod(params[25]);
    md->data->ask_volumn4      = std::stod(params[26]);
    md->data->ask_price5       = std::stod(params[27]);
    md->data->ask_volumn5      = std::stod(params[28]);
#endif

    libcpp::string_to_bytes(params[30].substr(0, 8), md->data->trading_day);
    libcpp::string_to_bytes(libcpp::string_util::fmt("{}:{}:{}", 
        params[30].substr(8, 2), params[30].substr(10, 2), params[30].substr(12, 2)), 
        md->data->action_time);

    md->data->highest_price    = std::stod(params[33]);
    md->data->lowest_price     = std::stod(params[34]);
    md->data->turnover         = std::stod(params[37]) * 10000.0;
    return true;
}

void tx::register_cb()
{
    _on_sub_rsp = std::bind(&tx::on_subscribe_market_data_rsp, this);
    _on_unsub_rsp = std::bind(&tx::on_unsubscribe_market_data_rsp, this);
    _on_md_ntf = std::bind(&tx::on_market_data_ntf, this, std::placeholders::_1);
}

void tx::on_subscribe_market_data_rsp()
{
    LOG_DEBUG("on_subscribe_market_data_rsp");
}

void tx::on_unsubscribe_market_data_rsp()
{
    LOG_DEBUG("on_unsubscribe_market_data_rsp");
}

void tx::on_market_data_ntf(std::vector<common::market_data_shm*>& mds)
{
    LOG_DEBUG("on_market_data_ntf with mds.size() ={} ", mds.size());
    for (common::market_data_shm* md : mds)
    {
        md->write();
        LOG_DEBUG("write market data to shared memory {}", md->fmt());
    }
}


}