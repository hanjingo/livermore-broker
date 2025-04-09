#include "market_data_shm.h"
#include <libcpp/util/string_util.hpp>

namespace common
{

void market_data_shm::reset()
{
    memset(data->trading_day, 0, sizeof(data->trading_day));
    memset(data->instrument_name, 0, sizeof(data->instrument_name));
    memset(data->instrument_id, 0, sizeof(data->instrument_id));
    memset(data->exchange_id, 0, sizeof(data->exchange_id));
    data->last_price = 0.0;
    data->pre_close_price = 0.0;
    data->open_price = 0.0;
    data->pre_settlement_price = 0.0;
    data->highest_price = 0.0;
    data->lowest_price = 0.0;
    data->close_price = 0.0;
    data->settlement_price = 0.0;
    data->upper_limit_price = 0.0;
    data->lower_limit_price = 0.0;
    data->average_price = 0.0;
    data->bid_price1 = 0.0;
    data->ask_price1 = 0.0;
    data->bid_price2 = 0.0;
    data->ask_price2 = 0.0;
    data->bid_price3 = 0.0;
    data->ask_price3 = 0.0;
    data->bid_price4 = 0.0;
    data->ask_price4 = 0.0;
    data->bid_price5 = 0.0;
    data->ask_price5 = 0.0;
    data->bid_volumn1 = 0.0;
    data->ask_volumn1 = 0.0;
    data->bid_volumn2 = 0.0;
    data->ask_volumn2 = 0.0;
    data->bid_volumn3 = 0.0;
    data->ask_volumn3 = 0.0;
    data->bid_volumn4 = 0.0;
    data->ask_volumn4 = 0.0;
    data->bid_volumn5 = 0.0;
    data->ask_volumn5 = 0.0;
    data->volume = 0.0;
    data->pre_open_interest = 0.0;
    data->open_interest = 0.0;
    data->trading_volumn = 0.0;
    data->turnover = 0.0;
    memset(data->action_time, 0, sizeof(data->action_time));
    data->action_ms = 0;
}

std::string market_data_shm::fmt()
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
        std::string(data->trading_day),
        std::string(data->instrument_name),
        std::string(data->instrument_id),
        std::string(data->exchange_id),
        data->last_price,
        data->pre_close_price,
        data->open_price,
        data->pre_settlement_price,
        data->highest_price,
        data->lowest_price,
        data->close_price,
        data->settlement_price,
        data->upper_limit_price,
        data->lower_limit_price,
        data->average_price,
        data->bid_price1,
        data->ask_price1,
        data->bid_price2,
        data->ask_price2,
        data->bid_price3,
        data->ask_price3,
        data->bid_price4,
        data->ask_price4,
        data->bid_price5,
        data->ask_price5,
        data->bid_volumn1,
        data->ask_volumn1,
        data->bid_volumn2,
        data->ask_volumn2,
        data->bid_volumn3,
        data->ask_volumn3,
        data->bid_volumn4,
        data->ask_volumn4,
        data->bid_volumn5,
        data->ask_volumn5,
        data->volume,
        data->pre_open_interest,
        data->open_interest,
        data->trading_volumn,
        data->turnover,
        std::string(data->action_time),
        data->action_ms
    );
}

bool market_data_shm::is_equal(const market_data_shm* rhs, std::string& memo)
{
    if (std::string(data->trading_day) != std::string(rhs->data->trading_day))
    {
        memo = "trading_day not equal";
        return false;
    }
    if (std::string(data->instrument_name) != std::string(rhs->data->instrument_name))
    {
        memo = "instrument_name not equal";
        return false;
    }
    if (std::string(data->instrument_id) == std::string(rhs->data->instrument_id))
    {
        memo = "instrument_id not equal";
        return false;
    }
    if (std::string(data->exchange_id) == std::string(rhs->data->exchange_id))
    {
        memo = "exchange_id not equal";
        return false;
    }
    if (data->last_price != rhs->data->last_price)
    {
        memo = "last_price not equal";
        return false;
    }
    if (data->pre_close_price != rhs->data->pre_close_price)
    {
        memo = "pre_close_price not equal";
        return false;
    }
    if (data->open_price != rhs->data->open_price)
    {
        memo = "open_price not equal";
        return false;
    }
    if (data->pre_settlement_price != rhs->data->pre_settlement_price)
    {
        memo = "pre_settlement_price not equal";
        return false;
    }
    if (data->highest_price != rhs->data->highest_price)
    {
        memo = "highest_price not equal";
        return false;
    }
    if (data->lowest_price != rhs->data->lowest_price)
    {
        memo = "lowest_price not equal";
        return false;
    }
    if (data->close_price != rhs->data->close_price)
    {
        memo = "close_price not equal";
        return false;
    }
    if (data->settlement_price != rhs->data->settlement_price)
    {
        memo = "settlement_price not equal";
        return false;
    }
    if (data->upper_limit_price != rhs->data->upper_limit_price)
    {
        memo = "upper_limit_price not equal";
        return false;
    }
    if (data->lower_limit_price != rhs->data->lower_limit_price)
    {
        memo = "lower_limit_price not equal";
        return false;
    }
    if (data->average_price != rhs->data->average_price)
    {
        memo = "average_price not equal";
        return false;
    }

#ifdef DEPTH_MARKET_DATA
    if (data->bid_price1 != rhs->data->bid_price1)
    {
        memo = "bid_price1 not equal";
        return false;
    }
    if (data->ask_price1 != rhs->data->ask_price1)
    {
        memo = "ask_price1 not equal";
        return false;
    }
    if (data->bid_price2 != rhs->data->bid_price2)
    {
        memo = "bid_price2 not equal";
        return false;
    }
    if (data->ask_price2 != rhs->data->bid_price2)
    {
        memo = "ask_price2 not equal";
        return false;
    }
    if (data->bid_price3 != rhs->data->bid_price3)
    {
        memo = "bid_price3 not equal";
        return false;
    }
    if (data->ask_price3 != rhs->data->ask_price3)
    {
        memo = "ask_price3 not equal";
        return false;
    }
    if (data->bid_price4 != rhs->data->bid_price4)
    {
        memo = "bid_price4 not equal";
        return false;
    }
    if (data->ask_price4 != rhs->data->ask_price4)
    {
        memo = "ask_price4 not equal";
        return false;
    }
    if (data->bid_price5 != rhs->data->bid_price5)
    {
        memo = "bid_price5 not equal";
        return false;
    }
    if (data->ask_price5 != rhs->data->ask_price5)
    {
        memo = "ask_price5 not equal";
        return false;
    }
    if (data->bid_volumn1 != rhs->data->bid_volumn1)
    {
        memo = "bid_volumn1 not equal";
        return false;
    }
    if (data->ask_volumn1 != rhs->data->ask_volumn1)
    {
        memo = "ask_volumn1 not equal";
        return false;
    }
    if (data->bid_volumn2 != rhs->data->bid_volumn2)
    {
        memo = "bid_volumn2 not equal";
        return false;
    }
    if (data->ask_volumn2 != rhs->data->ask_volumn2)
    {
        memo = "ask_volumn2 not equal";
        return false;
    }
    if (data->bid_volumn3 != rhs->data->bid_volumn3)
    {
        memo = "bid_volumn3 not equal";
        return false;
    }
    if (data->ask_volumn3 != rhs->data->ask_volumn3)
    {
        memo = "ask_volumn3 not equal";
        return false;
    }
    if (data->bid_volumn4 != rhs->data->bid_volumn4)
    {
        memo = "bid_volumn4 not equal";
        return false;
    }
    if (data->ask_volumn4 != rhs->data->ask_volumn4)
    {
        memo = "ask_volumn4 not equal";
        return false;
    }
    if (data->bid_volumn5 != rhs->data->bid_volumn5)
    {
        memo = "bid_volumn5 not equal";
        return false;
    }
    if (data->ask_volumn5 != rhs->data->ask_volumn5)
    {
        memo = "ask_volumn5 not equal";
        return false;
    }
#endif

    if (data->volume != rhs->data->volume)
    {
        memo = "volume not equal";
        return false;
    }
    if (data->pre_open_interest != rhs->data->pre_open_interest)
    {
        memo = "pre_open_interest not equal";
        return false;
    }
    if (data->open_interest != rhs->data->open_interest)
    {
        memo = "open_interest not equal";
        return false;
    }
    if (data->trading_volumn != rhs->data->trading_volumn)
    {
        memo = "trading_volumn not equal";
        return false;
    }
    if (data->turnover != rhs->data->turnover)
    {
        memo = "turnover not equal";
        return false;
    }
    if (std::string(data->action_time) != std::string(rhs->data->action_time))
    {
        memo = "action_time not equal";
        return false;
    }
    if (data->action_ms != rhs->data->action_ms)
    {
        memo = "action_ms not equal";
        return false;
    }

    return true;
}

void market_data_shm::copy_from(market_data* dst, const market_data* src)
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

void market_data_shm::write(market_data* md)
{
    if (md != nullptr)
        market_data_shm::copy_from(data, md);

    *flag = 1;
}

void market_data_shm::read(market_data* md)
{
    if (*flag != 1)
        return;
        
    if (md != nullptr)
        market_data_shm::copy_from(md, data);

    *flag = 0;
}

}