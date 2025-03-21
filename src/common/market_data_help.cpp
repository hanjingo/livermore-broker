#include "market_data_help.h"
#include <libcpp/util/string_util.hpp>

namespace common
{

void md_reset(market_data* md)
{
    memset(md->trading_day, 0, sizeof(md->trading_day));
    memset(md->instrument_name, 0, sizeof(md->instrument_name));
    memset(md->instrument_id, 0, sizeof(md->instrument_id));
    memset(md->exchange_id, 0, sizeof(md->exchange_id));
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
    md->bid_volumn1 = 0.0;
    md->ask_volumn1 = 0.0;
    md->bid_volumn2 = 0.0;
    md->ask_volumn2 = 0.0;
    md->bid_volumn3 = 0.0;
    md->ask_volumn3 = 0.0;
    md->bid_volumn4 = 0.0;
    md->ask_volumn4 = 0.0;
    md->bid_volumn5 = 0.0;
    md->ask_volumn5 = 0.0;
    md->volume = 0.0;
    md->pre_open_interest = 0.0;
    md->open_interest = 0.0;
    md->trading_volumn = 0.0;
    md->turnover = 0.0;
    memset(md->action_time, 0, sizeof(md->action_time));
    md->action_ms = 0;
}

std::string md_fmt(const market_data* md)
{
    return libcpp::string_util::fmt(
        R"([trading_day:{}, instrument_name:{}, instrument_id:{}, exchange_id:{}, last_price:{}, 
            pre_close_price:{}, open_price:{}, pre_settlement_price:{}, highest_price:{}, lowest_price:{},
            close_price:{}, settlement_price:{}, upper_limit_price:{}, lower_limit_price:{}, average_price:{},
            bid_price1:{}, ask_price1:{}, bid_price2:{}, ask_price2:{}, bid_price3:{}, ask_price3:{},
            bid_price4:{}, ask_price4:{}, bid_price5:{}, ask_price5:{}, bid_volumn1:{}, ask_volumn1:{},
            bid_volumn2:{}, ask_volumn2:{}, bid_volumn3:{}, ask_volumn3:{}, bid_volumn4:{}, ask_volumn4:{},
            bid_volumn5:{}, ask_volumn5:{}, volume:{}, pre_open_interest:{}, open_interest:{}, 
            trading_volumn:{}, turnover:{}, action_time:{}, action_ms:{}])",
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
        md->bid_volumn1,
        md->ask_volumn1,
        md->bid_volumn2,
        md->ask_volumn2,
        md->bid_volumn3,
        md->ask_volumn3,
        md->bid_volumn4,
        md->ask_volumn4,
        md->bid_volumn5,
        md->ask_volumn5,
        md->volume,
        md->pre_open_interest,
        md->open_interest,
        md->trading_volumn,
        md->turnover,
        std::string(md->action_time),
        md->action_ms
    );
}

bool md_equal(const market_data* md1, const market_data* md2, std::string& memo)
{
    if (std::string(md1->trading_day) != std::string(md2->trading_day))
    {
        memo = "trading_day not equal";
        return false;
    }
    if (std::string(md1->instrument_name) != std::string(md2->instrument_name))
    {
        memo = "instrument_name not equal";
        return false;
    }
    if (std::string(md1->instrument_id) == std::string(md2->instrument_id))
    {
        memo = "instrument_id not equal";
        return false;
    }
    if (std::string(md1->exchange_id) == std::string(md2->exchange_id))
    {
        memo = "exchange_id not equal";
        return false;
    }
    if (md1->last_price != md2->last_price)
    {
        memo = "last_price not equal";
        return false;
    }
    if (md1->pre_close_price != md2->pre_close_price)
    {
        memo = "pre_close_price not equal";
        return false;
    }
    if (md1->open_price != md2->open_price)
    {
        memo = "open_price not equal";
        return false;
    }
    if (md1->pre_settlement_price != md2->pre_settlement_price)
    {
        memo = "pre_settlement_price not equal";
        return false;
    }
    if (md1->highest_price != md2->highest_price)
    {
        memo = "highest_price not equal";
        return false;
    }
    if (md1->lowest_price != md2->lowest_price)
    {
        memo = "lowest_price not equal";
        return false;
    }
    if (md1->close_price != md2->close_price)
    {
        memo = "close_price not equal";
        return false;
    }
    if (md1->settlement_price != md2->settlement_price)
    {
        memo = "settlement_price not equal";
        return false;
    }
    if (md1->upper_limit_price != md2->upper_limit_price)
    {
        memo = "upper_limit_price not equal";
        return false;
    }
    if (md1->lower_limit_price != md2->lower_limit_price)
    {
        memo = "lower_limit_price not equal";
        return false;
    }
    if (md1->average_price != md2->average_price)
    {
        memo = "average_price not equal";
        return false;
    }

#ifdef DEPTH_MARKET_DATA
    if (md1->bid_price1 != md2->bid_price1)
    {
        memo = "bid_price1 not equal";
        return false;
    }
    if (md1->ask_price1 != md2->ask_price1)
    {
        memo = "ask_price1 not equal";
        return false;
    }
    if (md1->bid_price2 != md2->bid_price2)
    {
        memo = "bid_price2 not equal";
        return false;
    }
    if (md1->ask_price2 != md2->bid_price2)
    {
        memo = "ask_price2 not equal";
        return false;
    }
    if (md1->bid_price3 != md2->bid_price3)
    {
        memo = "bid_price3 not equal";
        return false;
    }
    if (md1->ask_price3 != md2->ask_price3)
    {
        memo = "ask_price3 not equal";
        return false;
    }
    if (md1->bid_price4 != md2->bid_price4)
    {
        memo = "bid_price4 not equal";
        return false;
    }
    if (md1->ask_price4 != md2->ask_price4)
    {
        memo = "ask_price4 not equal";
        return false;
    }
    if (md1->bid_price5 != md2->bid_price5)
    {
        memo = "bid_price5 not equal";
        return false;
    }
    if (md1->ask_price5 != md2->ask_price5)
    {
        memo = "ask_price5 not equal";
        return false;
    }
    if (md1->bid_volumn1 != md2->bid_volumn1)
    {
        memo = "bid_volumn1 not equal";
        return false;
    }
    if (md1->ask_volumn1 != md2->ask_volumn1)
    {
        memo = "ask_volumn1 not equal";
        return false;
    }
    if (md1->bid_volumn2 != md2->bid_volumn2)
    {
        memo = "bid_volumn2 not equal";
        return false;
    }
    if (md1->ask_volumn2 != md2->ask_volumn2)
    {
        memo = "ask_volumn2 not equal";
        return false;
    }
    if (md1->bid_volumn3 != md2->bid_volumn3)
    {
        memo = "bid_volumn3 not equal";
        return false;
    }
    if (md1->ask_volumn3 != md2->ask_volumn3)
    {
        memo = "ask_volumn3 not equal";
        return false;
    }
    if (md1->bid_volumn4 != md2->bid_volumn4)
    {
        memo = "bid_volumn4 not equal";
        return false;
    }
    if (md1->ask_volumn4 != md2->ask_volumn4)
    {
        memo = "ask_volumn4 not equal";
        return false;
    }
    if (md1->bid_volumn5 != md2->bid_volumn5)
    {
        memo = "bid_volumn5 not equal";
        return false;
    }
    if (md1->ask_volumn5 != md2->ask_volumn5)
    {
        memo = "ask_volumn5 not equal";
        return false;
    }
#endif

    if (md1->volume != md2->volume)
    {
        memo = "volume not equal";
        return false;
    }
    if (md1->pre_open_interest != md2->pre_open_interest)
    {
        memo = "pre_open_interest not equal";
        return false;
    }
    if (md1->open_interest != md2->open_interest)
    {
        memo = "open_interest not equal";
        return false;
    }
    if (md1->trading_volumn != md2->trading_volumn)
    {
        memo = "trading_volumn not equal";
        return false;
    }
    if (md1->turnover != md2->turnover)
    {
        memo = "turnover not equal";
        return false;
    }
    if (std::string(md1->action_time) != std::string(md2->action_time))
    {
        memo = "action_time not equal";
        return false;
    }
    if (md1->action_ms != md2->action_ms)
    {
        memo = "action_ms not equal";
        return false;
    }

    return true;
}

void md_copy(market_data* dst, market_data* src)
{
    memcpy(dst->trading_day, src->trading_day, sizeof(dst->trading_day));
    memcpy(dst->instrument_name, src->instrument_name, sizeof(dst->instrument_name));
    memcpy(dst->instrument_id, src->instrument_id, sizeof(dst->instrument_id));
    memcpy(dst->exchange_id, src->instrument_id, sizeof(dst->instrument_id));
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
#ifdef DEPTH_MARKET_DATA
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
    dst->bid_volumn1 = src->bid_volumn1;
    dst->ask_volumn1 = src->ask_volumn1;
    dst->bid_volumn2 = src->bid_volumn2;
    dst->ask_volumn2 = src->ask_volumn2;
    dst->bid_volumn3 = src->bid_volumn3;
    dst->ask_volumn3 = src->ask_volumn3;
    dst->bid_volumn4 = src->bid_volumn4;
    dst->ask_volumn4 = src->ask_volumn4;
    dst->bid_volumn5 = src->bid_volumn5;
    dst->ask_volumn5 = src->ask_volumn5;
#endif
    dst->volume = src->volume;
    dst->pre_open_interest = src->pre_open_interest;
    dst->open_interest = src->open_interest;
    dst->trading_volumn = src->trading_volumn;
    dst->turnover = src->turnover;
    memcpy(dst->action_time, src->action_time, sizeof(dst->action_time)),
    dst->action_ms = src->action_ms;
}

}