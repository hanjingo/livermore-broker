#include "xtp.h"

#include <cstring>

#include <libcpp/log/logger.hpp>
#include <libcpp/util/string_util.hpp>

#include "ipc.h"

namespace quote
{

xtp::stat xtp::status_change(const stat new_stat)
{
	xtp::stat old_stat = _stat.load();
	switch (new_stat)
	{
		case stat::logging: { 
			if (old_stat != stat::logged_out)
				return old_stat;
			break; 
		}
		case stat::logged: { 
			if (old_stat != stat::logging)
				return old_stat;
			break; 
		}
		case stat::logging_out: { 
			if (old_stat != stat::logged)
				return old_stat;
			break;
		}
        case stat::logged_out: { 
			break;
		}
		default: return old_stat;
	}
	
	return _stat.compare_exchange_weak(old_stat, new_stat) ? new_stat : old_stat;
}

error xtp::init(
    const uint8_t client_id, 
    const char *save_file_path, 
    const int log_level,
    uint32_t heatbeat_interval_sec, 
    uint32_t buff_size_mb)
{
    LOG_DEBUG("xpt::init enter with client_id={0}, save_file_path={1}, log_level={2}, heatbeat_interval_sec={3}, buff_size_mb={4}", 
        client_id, save_file_path, log_level, heatbeat_interval_sec, buff_size_mb);

    if (status_change(stat::logged_out) != stat::logged_out)
        return error::xtp_current_stat_not_allowd_init;

    _api = XTP::API::QuoteApi::CreateQuoteApi(client_id, save_file_path, (XTP_LOG_LEVEL)(log_level));
    if (_api == nullptr)
        return error::xtp_null;
    
    _api->Logout(); // whatever logout first;
    _api->SetHeartBeatInterval(heatbeat_interval_sec);
	_api->SetUDPBufferSize(buff_size_mb);
    _api->RegisterSpi(this);
    return error::ok;
}

error xtp::register_addr(
    const std::vector<std::string>& addrs, 
    bool using_udp,
    const std::string& local_ip)
{
    LOG_DEBUG("xtp::register_addr enter with addrs.size()={0}, using_udp={1}, local_ip={2}", 
        addrs.size(), using_udp, local_ip);
    if (addrs.empty())
		return error::xtp_addr_empty;

    for (int i = 0; i < addrs.size() && i < XTP_ADDR_N; ++i)
    {
        auto tmp = libcpp::string_util::split(addrs[i], ":");
        if (tmp.size() < 2)
            return error::xtp_addr_invalid;

        _addrs[i] = std::make_pair<std::string, uint16_t>(
            std::move(tmp[0]), std::move(std::stoi(tmp[1])));
    }

    _protocol = (using_udp) ? XTP_PROTOCOL_UDP : XTP_PROTOCOL_TCP;
    _local_ip = local_ip;
    return error::ok;
}

error xtp::login(const char* user, const char* password, uint32_t timeout_ms)
{
    LOG_DEBUG("xtp::login enter");
    if (status_change(stat::logging) != stat::logging)
		return error::xtp_current_status_not_allowed_login;

    auto err = error::ok;
    int i = 0;
    for (; i < XTP_ADDR_N; ++i)
    {
        if (_addrs[i].first.empty())
            continue;

        auto ret = _api->Login(_addrs[i].first.c_str(), _addrs[i].second, user, password, _protocol, _local_ip.c_str());
        switch (ret)
        {
            case 0:  {err = error::ok; break;}
            case -1: {err = error::xtp_connect_serv_fail; break;}
            case -2: {err = error::xtp_connect_already_exist; break;}
            case -3: {err = error::xtp_input_error; break;}
            default: {err = error::xtp_unknow_error; break;}
        }

        LOG_DEBUG("xtp login with ip={}, port={}, user={}, password={}, _protocol={}, _local_ip={}", 
            _addrs[i].first, _addrs[i].second, user, password, int(_protocol), _local_ip);
        if (err == error::ok)
            break;

        XTPRI* err = _api->GetApiLastError();
        LOG_DEBUG("get login fail last error with error_id={0}, error_msg={1}", err->error_id, err->error_msg);
    }

    return (i == XTP_ADDR_N) ? error::xtp_login_fail : error::ok;
}

error xtp::logout()
{
    if (status_change(stat::logging_out) != stat::logging_out)
        return error::xtp_current_status_not_allowed_logging_out;

    int ret = _api->Logout();
    if (ret != 0)
        return error::xtp_logout_fail;

    return error::ok;
}

error xtp::subscribe_market_data(std::unordered_map<int, std::vector<std::string> >& instruments)
{
    std::vector<std::string> topics;
    for (int i = 1; i < 4; i++)
    {
        topics = instruments[i];
        if (topics.empty())
            continue;

        char* *buf = new char*[topics.size()];
        for (int i = 0; i < topics.size(); i++)
        {
            strcpy(buf[i], topics[i].c_str());
        }
        int ret = _api->SubscribeMarketData(buf, topics.size(), (XTP_EXCHANGE_TYPE)(i));

        for (int j = 0; j < topics.size(); j++) {
            delete[] buf[j];
            buf[j] = NULL;
        }
        delete[] buf;
        buf = NULL;

        if (ret != 0)
            return error::xtp_subscribe_fail;
    }

    return error::ok;
}

error xtp::unsubscribe_market_data(std::unordered_map<int, std::vector<std::string> >& instruments)
{
    std::vector<std::string> topics;
    for (int i = 1; i < 4; i++)
    {
        topics = instruments[i];
        if (topics.empty())
            continue;

        char* *buf = new char*[topics.size()];
        for (int i = 0; i < topics.size(); i++)
        {
            strcpy(buf[i], topics[i].c_str());
        }
        int ret = _api->UnSubscribeMarketData(buf, topics.size(), (XTP_EXCHANGE_TYPE)(i));

        for (int j = 0; j < topics.size(); j++) {
            delete[] buf[j];
            buf[j] = NULL;
        }
        delete[] buf;
        buf = NULL;

        if (ret != 0)
            return error::xtp_unsubscribe_fail;
    }

    return error::ok;
}

error xtp::wait()
{
	// run thread, wait msg
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return error::ok;
}

/////////////////////////////////// callback function /////////////////////////////////////////

void xtp::OnDisconnected(int reason)
{
    if (status_change(stat::logged_out) != stat::logged_out)
	{
		LOG_ERROR("xtp logged out stat change fail");
		return;
	}
	
	LOG_DEBUG("xtp disconnected with reason={}", common::err_to_hex(reason));
}

void xtp::OnError(XTPRI *error_info)
{
    LOG_ERROR("recv xtp error with error_id={0}, error_msg={1}", 
        common::err_to_hex(error_info->error_id), error_info->error_msg);
}

void xtp::OnTickByTickLossRange(int begin_seq, int end_seq)
{
    LOG_DEBUG("OnTickByTickLossRange");
}

void xtp::OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    if (error_info != nullptr && error_info->error_id != 0)
        LOG_ERROR("subscribe market data fail with error code={}", error_info->error_id);

    LOG_DEBUG("OnSubMarketData");
}

void xtp::OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    if (error_info != nullptr && error_info->error_id != 0)
        LOG_ERROR("unsubscribe market data fail with error code={}", error_info->error_id);

    LOG_DEBUG("OnUnSubMarketData");
}

void xtp::OnDepthMarketData(
        XTPMD *market_data, 
        int64_t bid1_qty[], 
        int32_t bid1_count, 
        int32_t max_bid1_count, 
        int64_t ask1_qty[], 
        int32_t ask1_count, 
        int32_t max_ask1_count)
{
    LOG_DEBUG("OnDepthMarketData");


}

void xtp::OnETFIOPVData(IOPV *iopv)
{
    LOG_DEBUG("");
}

void xtp::OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    LOG_DEBUG("");
}

void xtp::OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    LOG_DEBUG("");
}

void xtp::OnOrderBook(XTPOB *order_book)
{
    LOG_DEBUG("");
}

void xtp::OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    LOG_DEBUG("");
}

void xtp::OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    LOG_DEBUG("");
}

void xtp::OnTickByTick(XTPTBT *tbt_data)
{
    LOG_DEBUG("");
}

void xtp::OnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnUnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnUnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnUnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last)
{
    LOG_DEBUG("");
}

void xtp::OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI *error_info, bool is_last)
{
    LOG_DEBUG("");
}

void xtp::OnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnUnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnUnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnUnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    LOG_DEBUG("");
}

void xtp::OnQueryAllTickersFullInfo(XTPQFI* ticker_info, XTPRI *error_info, bool is_last)
{
    LOG_DEBUG("");
}

void xtp::OnQueryAllNQTickersFullInfo(XTPNQFI* ticker_info, XTPRI *error_info, bool is_last)
{
    LOG_DEBUG("");
}

void xtp::OnRebuildQuoteServerDisconnected(int reason)
{
    LOG_DEBUG("");
}

void xtp::OnRequestRebuildQuote(XTPQuoteRebuildResultRsp* rebuild_result)
{
    LOG_DEBUG("");
}

void xtp::OnRebuildTickByTick(XTPTBT *tbt_data)
{
    LOG_DEBUG("");
}

void xtp::OnRebuildMarketData(XTPMD *md_data)
{
    LOG_DEBUG("");
}

}