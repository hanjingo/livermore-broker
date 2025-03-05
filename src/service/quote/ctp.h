#ifndef CTP_H
#define CTP_H

#include <thread>
#include <atomic>
#include <vector>
#include <unordered_map>

#include <ctp-traderAPI/ThostFtdcMdApi.h>
#include <ctp-traderAPI/ThostFtdcUserApiStruct.h>
#include <ctp-traderAPI/ThostFtdcUserApiDataType.h>

#include "error.h"

#ifndef INSTRUMENT_LEN
#define INSTRUMENT_LEN 7
#endif

namespace quote
{

class ctp : public CThostFtdcMdSpi
{
public:
    enum class stat : uint8_t
    {
        disconnected = 0x1,
        connecting,
        connected,
        logging,
        logged,
        logging_out,
    };

public:
    ctp() { reset(); }
    ~ctp() {}

public:
    inline stat status() { return _stat.load(); }
    ctp::stat status_change(const ctp::stat new_stat);
    inline int req_id() { return _req_id.load(); }
    inline int id_inc() { int old = _req_id.load(); return _req_id.compare_exchange_weak(old, old + 1) ? old : old + 1; }
    inline void reset() { _stat.store(stat::disconnected); _req_id.store(0); }

    error connect(const int port, 
        const char* ip, 
        const char* psz_flow_path = "", 
        const bool is_using_udp = false, 
        const bool is_multicast = false,
        unsigned int timeout_ms = 3000);
    error login(unsigned int retry_times = 1, unsigned int retry_interval_ms = 1000);
    error logout();
    error subscribe_market_data(const std::vector<std::string>& instruments = {});
    error unsubscribe_market_data(const std::vector<std::string>& instruments = {});
    error wait();

public:
    void OnFrontConnected() override;
    void OnFrontDisconnected(int nReason) override;
    void OnHeartBeatWarning(int nTimeLapse) override;
    void OnRspUserLogin(
        CThostFtdcRspUserLoginField *pRspUserLogin, 
        CThostFtdcRspInfoField *pRspInfo, 
        int nRequestID, 
        bool bIsLast) override;
    void OnRspUserLogout(
        CThostFtdcUserLogoutField *pUserLogout, 
        CThostFtdcRspInfoField *pRspInfo, 
        int nRequestID, 
        bool bIsLast) override;
    void OnRspError(
        CThostFtdcRspInfoField *pRspInfo, 
        int nRequestID, 
        bool bIsLast) override;
    void OnRspSubMarketData(
        CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
        CThostFtdcRspInfoField *pRspInfo, 
        int nRequestID, 
        bool bIsLast) override;
    void OnRspUnSubMarketData(
        CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
        CThostFtdcRspInfoField *pRspInfo, 
        int nRequestID, 
        bool bIsLast) override;
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) override;
    void OnRspSubForQuoteRsp(
        CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
        CThostFtdcRspInfoField *pRspInfo, 
        int nRequestID, 
        bool bIsLast) override;
    void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) override;

private:
    CThostFtdcMdApi* _mdapi;
    std::atomic<ctp::stat> _stat;

    std::unordered_map<std::string, CThostFtdcDepthMarketDataField*> _m_market_data;

    std::atomic<int> _req_id;
    int _login_retry_times = 0;
};

}

#endif