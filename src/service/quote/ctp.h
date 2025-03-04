#ifndef CTP_H
#define CTP_H

#include <stdio.h>
#include <thread>
#include <atomic>

#include <ctp-traderAPI/ThostFtdcMdApi.h>
#include <ctp-traderAPI/ThostFtdcUserApiStruct.h>
#include <ctp-traderAPI/ThostFtdcUserApiDataType.h>

#include <libcpp/log/logger.hpp>
#include <libcpp/util/string_util.hpp>

#include "error.h"

namespace quote
{

class ctp : public CThostFtdcMdSpi, public CThostFtdcMdApi
{
public:
    enum class stat : uint8_t
    {
        connecting = 0x1,
        connected,
        disconnected,
        logging,
        logged,
        logging_out,
    };

public:
    ctp() : _mdapi{nullptr} {}
    ~ctp() {}

public:
    inline stat status() { return _stat.load(); }

    error connect(const int port, 
                  const char* ip, 
                  const char* psz_flow_path = "", 
                  const bool is_using_udp = false, 
                  const bool is_multicast = false,
                  const unsigned int timeout_dur_ms = 3000);
    error login(unsigned int retry_times = 1, unsigned int retry_interval_ms = 1000);
    error logout();
    error subscribe(const std::vector<std::string>& instruments = {});
    ctp::stat status_change(const ctp::stat new_stat);

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
    char** _instruments;
    unsigned int _instruments_row = 0;
    int _request_id = 1;
    int _login_retry_times = 0;
    int _login_retry_interval_ms = 100;
};
    
}

#endif