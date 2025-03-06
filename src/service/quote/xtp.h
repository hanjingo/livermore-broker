#ifndef XTP_H
#define XTP_H

#include <atomic>
#include <vector>
#include <xtp/xtp_quote_api.h>

#include "error.h"

namespace quote
{

class xtp : public XTP::API::QuoteSpi
{
public:
    enum class stat : uint8_t
    {
        logging_out,
        logging,
        logged,
    };

public:
    xtp() {}
    ~xtp() {}

public:
    inline xtp::stat status() { return _stat.load(); }
    error init(
        const uint8_t client_id, 
        const char *save_file_path, 
        const int log_level=XTP_LOG_LEVEL_DEBUG,
        uint32_t heatbeat_interval_sec = 3000, 
        uint32_t buff_size = 4096);
    error login(
        const std::string& addr, 
        const char* user, 
        const char* password, 
        bool using_udp = false, 
        const char* local_ip = NULL, 
        uint32_t timeout_ms = 3000);

public:
    virtual void OnDisconnected(int reason) override;

	virtual void OnError(XTPRI *error_info) override;

	virtual void OnTickByTickLossRange(int begin_seq, int end_seq) override;

    virtual void OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) override;

	virtual void OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last) override;

	virtual void OnDepthMarketData(
        XTPMD *market_data, 
        int64_t bid1_qty[], 
        int32_t bid1_count, 
        int32_t max_bid1_count, 
        int64_t ask1_qty[], 
        int32_t ask1_count, 
        int32_t max_ask1_count) override;

	virtual void OnETFIOPVData(IOPV *iopv) override;

	virtual void OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last) override;

	virtual void OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last) override;

	virtual void OnOrderBook(XTPOB *order_book) override;

	virtual void OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last) override;

    virtual void OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last) override;

    virtual void OnTickByTick(XTPTBT *tbt_data) override;

    virtual void OnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnUnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnUnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnUnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last) override;

    virtual void OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI *error_info, bool is_last) override;

    virtual void OnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnUnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnUnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnUnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info) override;

    virtual void OnQueryAllTickersFullInfo(XTPQFI* ticker_info, XTPRI *error_info, bool is_last) override;

    virtual void OnQueryAllNQTickersFullInfo(XTPNQFI* ticker_info, XTPRI *error_info, bool is_last) override;

    virtual void OnRebuildQuoteServerDisconnected(int reason) override;

    virtual void OnRequestRebuildQuote(XTPQuoteRebuildResultRsp* rebuild_result) override;

    virtual void OnRebuildTickByTick(XTPTBT *tbt_data) override;

    virtual void OnRebuildMarketData(XTPMD *md_data) override;

private:
    XTP::API::QuoteApi* _api = nullptr;
    std::atomic<xtp::stat> _stat;
};

}

#endif