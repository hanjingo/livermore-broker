#ifndef API_JSON_H
#define API_JSON_H

#include <vector>
#include <libcpp/encoding/bytes.hpp>
#include <libcpp/encoding/json.hpp>
#include <libcpp/log/logger.hpp>

#include "msg.h"

namespace broadcast::api::json
{

void md_to_json(const std::vector<common::market_data_shm*>& mds, libcpp::json& arr)
{
    for (auto md : mds)
    {
        libcpp::json js;
        js["trading_day"] = md->data->trading_day;
        js["instrument_name"] = md->data->instrument_name;
        js["instrument_id"] = md->data->instrument_id;
        js["exchange_id"] = md->data->exchange_id;
        js["last_price"] = md->data->last_price;
        js["pre_close_price"] = md->data->pre_close_price;
        js["open_price"] = md->data->open_price;
        js["pre_settlement_price"] = md->data->pre_settlement_price;
        js["highest_price"] = md->data->highest_price;
        js["lowest_price"] = md->data->lowest_price;
        js["close_price"] = md->data->close_price;
        js["settlement_price"] = md->data->settlement_price;
        js["upper_limit_price"] = md->data->upper_limit_price;
        js["lower_limit_price"] = md->data->lower_limit_price;
        js["average_price"] = md->data->average_price;
#ifdef DEPTH_MARKET_DATA
        js["bid_price1"] = md->data->bid_price1;
        js["ask_price1"] = md->data->ask_price1;
        js["bid_price2"] = md->data->bid_price2;
        js["ask_price2"] = md->data->ask_price2;
        js["bid_price3"] = md->data->bid_price3;
        js["ask_price3"] = md->data->ask_price3;
        js["bid_price4"] = md->data->bid_price4;
        js["ask_price4"] = md->data->ask_price4;
        js["bid_price5"] = md->data->bid_price5;
        js["ask_price5"] = md->data->ask_price5;
        js["bid_volumn1"] = md->data->bid_volumn1;
        js["ask_volumn1"] = md->data->ask_volumn1;
        js["bid_volumn2"] = md->data->bid_volumn2;
        js["ask_volumn2"] = md->data->ask_volumn2;
        js["bid_volumn3"] = md->data->bid_volumn3;
        js["ask_volumn3"] = md->data->ask_volumn3;
        js["bid_volumn4"] = md->data->bid_volumn4;
        js["ask_volumn4"] = md->data->ask_volumn4;
        js["bid_volumn5"] = md->data->bid_volumn5;
        js["ask_volumn5"] = md->data->ask_volumn5;
#endif
        js["volume"] = md->data->volume;
        js["pre_open_interest"] = md->data->pre_open_interest;
        js["open_interest"] = md->data->open_interest;
        js["trading_volumn"] = md->data->trading_volumn;
        js["turnover"] = md->data->turnover;
        js["action_time"] = md->data->action_time;
        js["action_ms"] = md->data->action_ms;

        arr.push_back(js);
    }
}

struct md_ntf : public common::msg<std::vector<common::market_data_shm*> >
{
    md_ntf() : common::msg<std::vector<common::market_data_shm*> >(
        0, 0, 0, 0, 0, common::encode_json, std::vector<common::market_data_shm*>()) {}
    ~md_ntf() {}

    std::size_t size() override 
    { 
        return payload.size() * 500 + head_len();
    }
    std::size_t encode(unsigned char* buf, const std::size_t size) override 
    {
        auto arr = libcpp::json::array();
        md_to_json(payload, arr);

        libcpp::json js;
        js["payload"] = arr;
        js["id"] = id;
        js["len"] = 0;
        js["seq"] = seq;
        js["time"] = time;
        js["crc16"] = crc16;
        js["encode_type"] = encode_type;
        js["len"] = js.size();

        auto str = js.dump(4);
        LOG_DEBUG("encode md_ntf to str with str.size()={}", str.size());
        if (size < str.size())
            return 0;
        memcpy(buf, str.c_str(), str.size());
        return str.size();
    }
};

}

#endif