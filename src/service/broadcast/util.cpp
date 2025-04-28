#include "util.h"

namespace broadcast
{

void md_to_json(market_data* md, libcpp::json& js)
{
    js["trading_day"] = md->trading_day;
    js["instrument_name"] = md->instrument_name;
    js["instrument_id"] = md->instrument_id;
    js["exchange_id"] = md->exchange_id;
    js["last_price"] = md->last_price;
    js["pre_close_price"] = md->pre_close_price;
    js["open_price"] = md->open_price;
    js["pre_settlement_price"] = md->pre_settlement_price;
    js["highest_price"] = md->highest_price;
    js["lowest_price"] = md->lowest_price;
    js["close_price"] = md->close_price;
    js["settlement_price"] = md->settlement_price;
    js["upper_limit_price"] = md->upper_limit_price;
    js["lower_limit_price"] = md->lower_limit_price;
    js["average_price"] = md->average_price;
#ifdef USE_DEEP_DATA
    js["bid_price1"] = md->bid_price1;
    js["ask_price1"] = md->ask_price1;
    js["bid_price2"] = md->bid_price2;
    js["ask_price2"] = md->ask_price2;
    js["bid_price3"] = md->bid_price3;
    js["ask_price3"] = md->ask_price3;
    js["bid_price4"] = md->bid_price4;
    js["ask_price4"] = md->ask_price4;
    js["bid_price5"] = md->bid_price5;
    js["ask_price5"] = md->ask_price5;
    js["bid_volume1"] = md->bid_volume1;
    js["ask_volume1"] = md->ask_volume1;
    js["bid_volume2"] = md->bid_volume2;
    js["ask_volume2"] = md->ask_volume2;
    js["bid_volume3"] = md->bid_volume3;
    js["ask_volume3"] = md->ask_volume3;
    js["bid_volume4"] = md->bid_volume4;
    js["ask_volume4"] = md->ask_volume4;
    js["bid_volume5"] = md->bid_volume5;
    js["ask_volume5"] = md->ask_volume5;
#endif
    js["volume"] = md->volume;
    js["pre_open_interest"] = md->pre_open_interest;
    js["open_interest"] = md->open_interest;
    js["turnover"] = md->turnover;
    js["action_time"] = md->action_time;
    js["action_ms"] = md->action_ms;
}

}