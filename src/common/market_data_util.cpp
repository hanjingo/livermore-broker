#include "market_data_util.h"
#include <libcpp/util/string_util.hpp>

namespace common
{

void md_util::reset(market_data* md)
{
    memset(md->trading_day, 0, sizeof(market_data::trading_day));
    memset(md->instrument_name, 0, sizeof(market_data::instrument_name));
    memset(md->instrument_id, 0, sizeof(market_data::instrument_id));
    memset(md->exchange_id, 0, sizeof(market_data::exchange_id));
    md->last_price = 0.0;
    md->pre_close_price = 0.0;
    md->open_price = 0.0;
    md->pre_settlement_price = 0.0;
    md->highest_price = 0.0;
    md->lowest_price = 0.0;
    md->close_price = 0.0;
    md->settlement_price = 0.0;
    md->upper_limit_price = 0.0;
    md->lower_limit_price = 0.0;
    md->average_price = 0.0;
#ifdef USE_DEEP_DATA
    md->bid_price1 = 0.0;
    md->ask_price1 = 0.0;
    md->bid_price2 = 0.0;
    md->ask_price2 = 0.0;
    md->bid_price3 = 0.0;
    md->ask_price3 = 0.0;
    md->bid_price4 = 0.0;
    md->ask_price4 = 0.0;
    md->bid_price5 = 0.0;
    md->ask_price5 = 0.0;
    md->bid_volume1 = 0.0;
    md->ask_volume1 = 0.0;
    md->bid_volume2 = 0.0;
    md->ask_volume2 = 0.0;
    md->bid_volume3 = 0.0;
    md->ask_volume3 = 0.0;
    md->bid_volume4 = 0.0;
    md->ask_volume4 = 0.0;
    md->bid_volume5 = 0.0;
    md->ask_volume5 = 0.0;
#endif
    md->volume = 0.0;
    md->pre_open_interest = 0.0;
    md->open_interest = 0.0;
    md->turnover = 0.0;
    memset(md->action_time, 0, sizeof(market_data::action_time));
    md->action_ms = 0;
}

std::string md_util::fmt(const market_data* md)
{
    return libcpp::string_util::fmt(
#ifdef USE_DEEP_DATA
        R"([trading_day:{}, instrument_name:{}, instrument_id:{}, exchange_id:{}, last_price:{}, 
            pre_close_price:{}, open_price:{}, pre_settlement_price:{}, highest_price:{}, lowest_price:{},
            close_price:{}, settlement_price:{}, upper_limit_price:{}, lower_limit_price:{}, average_price:{},
            bid_price1:{}, ask_price1:{}, bid_price2:{}, ask_price2:{}, bid_price3:{}, ask_price3:{},
            bid_price4:{}, ask_price4:{}, bid_price5:{}, ask_price5:{}, bid_volume1:{}, ask_volume1:{},
            bid_volume2:{}, ask_volume2:{}, bid_volume3:{}, ask_volume3:{}, bid_volume4:{}, ask_volume4:{}, bid_volume5:{}, ask_volume5:{}, 
            volume:{}, pre_open_interest:{}, open_interest:{}, 
            turnover:{}, action_time:{}, action_ms:{}])",
#else
        R"([trading_day:{}, instrument_name:{}, instrument_id:{}, exchange_id:{}, last_price:{}, 
            pre_close_price:{}, open_price:{}, pre_settlement_price:{}, highest_price:{}, lowest_price:{},
            close_price:{}, settlement_price:{}, upper_limit_price:{}, lower_limit_price:{}, average_price:{},
            volume:{}, pre_open_interest:{}, open_interest:{}, 
            turnover:{}, action_time:{}, action_ms:{}])",
#endif
        std::string(md->trading_day),
        std::string(md->instrument_name),
        std::string(md->instrument_id),
        std::string(md->exchange_id),
        md->last_price,
        md->pre_close_price,
        md->open_price,
        md->pre_settlement_price,
        md->highest_price,
        md->lowest_price,
        md->close_price,
        md->settlement_price,
        md->upper_limit_price,
        md->lower_limit_price,
        md->average_price,
#ifdef USE_DEEP_DATA
        md->bid_price1,
        md->ask_price1,
        md->bid_price2,
        md->ask_price2,
        md->bid_price3,
        md->ask_price3,
        md->bid_price4,
        md->ask_price4,
        md->bid_price5,
        md->ask_price5,
        md->bid_volume1,
        md->ask_volume1,
        md->bid_volume2,
        md->ask_volume2,
        md->bid_volume3,
        md->ask_volume3,
        md->bid_volume4,
        md->ask_volume4,
        md->bid_volume5,
        md->ask_volume5,
#endif
        md->volume,
        md->pre_open_interest,
        md->open_interest,
        md->turnover,
        std::string(md->action_time),
        md->action_ms
    );
}

bool md_util::is_equal(const market_data* lhs, const market_data* rhs, std::string& memo)
{
    if (std::string(lhs->trading_day) != std::string(rhs->trading_day))
    {
        memo = "trading_day not equal";
        return false;
    }
    if (std::string(lhs->instrument_name) != std::string(rhs->instrument_name))
    {
        memo = "instrument_name not equal";
        return false;
    }
    if (std::string(lhs->instrument_id) == std::string(rhs->instrument_id))
    {
        memo = "instrument_id not equal";
        return false;
    }
    if (std::string(lhs->exchange_id) == std::string(rhs->exchange_id))
    {
        memo = "exchange_id not equal";
        return false;
    }
    if (lhs->last_price != rhs->last_price)
    {
        memo = "last_price not equal";
        return false;
    }
    if (lhs->pre_close_price != rhs->pre_close_price)
    {
        memo = "pre_close_price not equal";
        return false;
    }
    if (lhs->open_price != rhs->open_price)
    {
        memo = "open_price not equal";
        return false;
    }
    if (lhs->pre_settlement_price != rhs->pre_settlement_price)
    {
        memo = "pre_settlement_price not equal";
        return false;
    }
    if (lhs->highest_price != rhs->highest_price)
    {
        memo = "highest_price not equal";
        return false;
    }
    if (lhs->lowest_price != rhs->lowest_price)
    {
        memo = "lowest_price not equal";
        return false;
    }
    if (lhs->close_price != rhs->close_price)
    {
        memo = "close_price not equal";
        return false;
    }
    if (lhs->settlement_price != rhs->settlement_price)
    {
        memo = "settlement_price not equal";
        return false;
    }
    if (lhs->upper_limit_price != rhs->upper_limit_price)
    {
        memo = "upper_limit_price not equal";
        return false;
    }
    if (lhs->lower_limit_price != rhs->lower_limit_price)
    {
        memo = "lower_limit_price not equal";
        return false;
    }
    if (lhs->average_price != rhs->average_price)
    {
        memo = "average_price not equal";
        return false;
    }

#ifdef USE_DEEP_DATA
    if (lhs->bid_price1 != rhs->bid_price1)
    {
        memo = "bid_price1 not equal";
        return false;
    }
    if (lhs->ask_price1 != rhs->ask_price1)
    {
        memo = "ask_price1 not equal";
        return false;
    }
    if (lhs->bid_price2 != rhs->bid_price2)
    {
        memo = "bid_price2 not equal";
        return false;
    }
    if(lhs->ask_price2 != rhs->bid_price2)
    {
        memo = "ask_price2 not equal";
        return false;
    }
    if(lhs->bid_price3 != rhs->bid_price3)
    {
        memo = "bid_price3 not equal";
        return false;
    }
    if(lhs->ask_price3 != rhs->ask_price3)
    {
        memo = "ask_price3 not equal";
        return false;
    }
    if(lhs->bid_price4 != rhs->bid_price4)
    {
        memo = "bid_price4 not equal";
        return false;
    }
    if(lhs->ask_price4 != rhs->ask_price4)
    {
        memo = "ask_price4 not equal";
        return false;
    }
    if(lhs->bid_price5 != rhs->bid_price5)
    {
        memo = "bid_price5 not equal";
        return false;
    }
    if(lhs->ask_price5 != rhs->ask_price5)
    {
        memo = "ask_price5 not equal";
        return false;
    }
    if(lhs->bid_volume1 != rhs->bid_volume1)
    {
        memo = "bid_volume1 not equal";
        return false;
    }
    if(lhs->ask_volume1 != rhs->ask_volume1)
    {
        memo = "ask_volume1 not equal";
        return false;
    }
    if(lhs->bid_volume2 != rhs->bid_volume2)
    {
        memo = "bid_volume2 not equal";
        return false;
    }
    if(lhs->ask_volume2 != rhs->ask_volume2)
    {
        memo = "ask_volume2 not equal";
        return false;
    }
    if(lhs->bid_volume3 != rhs->bid_volume3)
    {
        memo = "bid_volume3 not equal";
        return false;
    }
    if(lhs->ask_volume3 != rhs->ask_volume3)
    {
        memo = "ask_volume3 not equal";
        return false;
    }
    if(lhs->bid_volume4 != rhs->bid_volume4)
    {
        memo = "bid_volume4 not equal";
        return false;
    }
    if(lhs->ask_volume4 != rhs->ask_volume4)
    {
        memo = "ask_volume4 not equal";
        return false;
    }
    if(lhs->bid_volume5 != rhs->bid_volume5)
    {
        memo = "bid_volume5 not equal";
        return false;
    }
    if(lhs->ask_volume5 != rhs->ask_volume5)
    {
        memo = "ask_volume5 not equal";
        return false;
    }
#endif

    if(lhs->volume != rhs->volume)
    {
        memo = "volume not equal";
        return false;
    }
    if(lhs->pre_open_interest != rhs->pre_open_interest)
    {
        memo = "pre_open_interest not equal";
        return false;
    }
    if(lhs->open_interest != rhs->open_interest)
    {
        memo = "open_interest not equal";
        return false;
    }
    if(lhs->turnover != rhs->turnover)
    {
        memo = "turnover not equal";
        return false;
    }
    if(std::string(lhs->action_time) != std::string(rhs->action_time))
    {
        memo = "action_time not equal";
        return false;
    }
    if(lhs->action_ms != rhs->action_ms)
    {
        memo = "action_ms not equal";
        return false;
    }

    return true;
}

void md_util::copy_from(market_data* dst, const market_data* src)
{
    memcpy(dst->trading_day, src->trading_day, sizeof(market_data::trading_day));
    memcpy(dst->instrument_name, src->instrument_name, sizeof(market_data::instrument_name));
    memcpy(dst->instrument_id, src->instrument_id, sizeof(market_data::instrument_id));
    memcpy(dst->exchange_id, src->instrument_id, sizeof(market_data::instrument_id));
    dst->last_price = src->last_price;
    dst->pre_close_price = src->pre_close_price;
    dst->open_price = src->open_price;
    dst->pre_settlement_price = src->pre_settlement_price;
    dst->highest_price = src->highest_price;
    dst->lowest_price = src->lowest_price;
    dst->close_price = src->close_price;
    dst->settlement_price = src->settlement_price;
    dst->upper_limit_price = src->upper_limit_price;
    dst->lower_limit_price = src->lower_limit_price;
    dst->average_price = src->average_price;
#ifdef USE_DEEP_DATA
    dst->bid_price1 = src->bid_price1;
    dst->ask_price1 = src->ask_price1;
    dst->bid_price2 = src->bid_price2;
    dst->ask_price2 = src->ask_price2;
    dst->bid_price3 = src->bid_price3;
    dst->ask_price3 = src->ask_price3;
    dst->bid_price4 = src->bid_price4;
    dst->ask_price4 = src->ask_price4;
    dst->bid_price5 = src->bid_price5;
    dst->ask_price5 = src->ask_price5;
    dst->bid_volume1 = src->bid_volume1;
    dst->ask_volume1 = src->ask_volume1;
    dst->bid_volume2 = src->bid_volume2;
    dst->ask_volume2 = src->ask_volume2;
    dst->bid_volume3 = src->bid_volume3;
    dst->ask_volume3 = src->ask_volume3;
    dst->bid_volume4 = src->bid_volume4;
    dst->ask_volume4 = src->ask_volume4;
    dst->bid_volume5 = src->bid_volume5;
    dst->ask_volume5 = src->ask_volume5;
#endif
    dst->volume = src->volume;
    dst->pre_open_interest = src->pre_open_interest;
    dst->open_interest = src->open_interest;
    dst->turnover = src->turnover;
    memcpy(dst->action_time, src->action_time, sizeof(market_data::action_time)),
    dst->action_ms = src->action_ms;
}

}