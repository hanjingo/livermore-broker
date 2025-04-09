#ifndef MARKET_DATA_H
#define MARKET_DATA_H

#ifndef DEPTH_MARKET_DATA
#define DEPTH_MARKET_DATA 1
#endif

extern "C" 
{

typedef char md_date_t[9];
typedef char md_time_t[9];
typedef int md_millisec_t;
typedef char md_instrument_id_t[31];
typedef char md_exchange_id_t[9];
typedef double md_price_t;
typedef double md_money_t;
typedef double md_volumn_t;
typedef char md_instrument_name_t[21];

#pragma pack(push, 8)
struct market_data
{
    md_date_t trading_day;
    md_instrument_name_t instrument_name;
    md_instrument_id_t instrument_id;
    md_exchange_id_t exchange_id;
    md_price_t last_price;
    md_price_t pre_close_price;
    md_price_t open_price;
    md_price_t pre_settlement_price;
    md_price_t highest_price;
    md_price_t lowest_price;
    md_price_t close_price;
    md_price_t settlement_price;
    md_price_t upper_limit_price;
    md_price_t lower_limit_price;
    md_price_t average_price;
#ifdef DEPTH_MARKET_DATA
    md_price_t bid_price1;
    md_price_t ask_price1;
    md_price_t bid_price2;
    md_price_t ask_price2;
    md_price_t bid_price3;
    md_price_t ask_price3;
    md_price_t bid_price4;
    md_price_t ask_price4;
    md_price_t bid_price5;
    md_price_t ask_price5;
    md_volumn_t bid_volumn1;
    md_volumn_t ask_volumn1;
    md_volumn_t bid_volumn2;
    md_volumn_t ask_volumn2;
    md_volumn_t bid_volumn3;
    md_volumn_t ask_volumn3;
    md_volumn_t bid_volumn4;
    md_volumn_t ask_volumn4;
    md_volumn_t bid_volumn5;
    md_volumn_t ask_volumn5;
#endif
    md_volumn_t volume;
    md_volumn_t pre_open_interest;
    md_volumn_t open_interest;
    md_volumn_t trading_volumn;
    md_money_t turnover;
    md_time_t action_time;
    md_millisec_t action_ms;
};
#pragma pack(pop)

}

#endif