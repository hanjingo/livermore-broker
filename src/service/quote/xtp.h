#ifndef XTP_H
#define XTP_H

#include <atomic>
#include <vector>
#include <unordered_map>
#include <xtp/xtp_quote_api.h>

#include "error.h"

#define XTP_ADDR_N 5

namespace quote
{

class xtp : public XTP::API::QuoteSpi
{
public:
    enum class stat : uint8_t
    {
        logged_out,
        logging,
        logged,
        logging_out,
    };

public:
    xtp() {}
    ~xtp() { if(_api != nullptr) {_api->Release();} }

public:
    inline xtp::stat status() { return _stat.load(); }
    xtp::stat status_change(const xtp::stat new_stat);
    error init(
        const uint8_t client_id, 
        const char *save_file_path, 
        const int log_level=XTP_LOG_LEVEL_DEBUG,
        uint32_t heatbeat_interval_sec = 3000, 
        uint32_t buff_size = 4096);

    error register_addr(
        const std::vector<std::string>& addrs = {}, 
        bool using_udp = false,
        const char* local_ip = NULL);

    error login(const char* user, const char* password, uint32_t timeout_ms = 3000);
    error logout();

    error subscribe_market_data(std::unordered_map<int, std::vector<std::string> >& instruments);
    error unsubscribe_market_data(std::unordered_map<int, std::vector<std::string> >& instruments);
    error wait();

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
    std::pair<std::string, uint16_t> _addrs[XTP_ADDR_N];
    XTP_PROTOCOL_TYPE _protocol = XTP_PROTOCOL_TCP;
    std::string _local_ip;
    std::atomic<int> _req_id;
};

}

#endif