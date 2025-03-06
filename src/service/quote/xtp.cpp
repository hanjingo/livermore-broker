#include "xtp.h"

namespace quote
{

error xtp::init(
    const uint8_t client_id, 
    const char *save_file_path, 
    const int log_level,
    uint32_t heatbeat_interval_sec, 
    uint32_t buff_size)
{
    _api = XTP::API::QuoteApi::CreateQuoteApi(client_id, save_file_path, XTP_LOG_LEVEL_DEBUG);
    if (_api == nullptr)
        return error::xtp_null;
        
    _api->RegisterSpi(this);
    return error::ok;
}

error xtp::login(
    const std::string& addr, 
    const char* user, 
    const char* password, 
    bool using_udp, 
    const char* local_ip, 
    uint32_t timeout_ms)
{
    return error::ok;
}

/////////////////////////////////// callback function /////////////////////////////////////////

void xtp::OnDisconnected(int reason)
{
    
}

void xtp::OnError(XTPRI *error_info)
{
    
}

void xtp::OnTickByTickLossRange(int begin_seq, int end_seq)
{
    
}

void xtp::OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    
}

void xtp::OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    
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
    
}

void xtp::OnETFIOPVData(IOPV *iopv)
{
    
}

void xtp::OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    
}

void xtp::OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    
}

void xtp::OnOrderBook(XTPOB *order_book)
{
    
}

void xtp::OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    
}

void xtp::OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
{
    
}

void xtp::OnTickByTick(XTPTBT *tbt_data)
{
    
}

void xtp::OnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnUnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnUnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnUnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last)
{
    
}

void xtp::OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI *error_info, bool is_last)
{
    
}

void xtp::OnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnUnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnUnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnUnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info)
{
    
}

void xtp::OnQueryAllTickersFullInfo(XTPQFI* ticker_info, XTPRI *error_info, bool is_last)
{
    
}

void xtp::OnQueryAllNQTickersFullInfo(XTPNQFI* ticker_info, XTPRI *error_info, bool is_last)
{
    
}

void xtp::OnRebuildQuoteServerDisconnected(int reason)
{
    
}

void xtp::OnRequestRebuildQuote(XTPQuoteRebuildResultRsp* rebuild_result)
{
    
}

void xtp::OnRebuildTickByTick(XTPTBT *tbt_data)
{
    
}

void xtp::OnRebuildMarketData(XTPMD *md_data)
{
    
}

}