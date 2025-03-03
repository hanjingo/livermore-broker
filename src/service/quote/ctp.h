#ifndef CTP_H
#define CTP_H

#include <stdio.h>
#include <thread>

#include <ctp-traderAPI/ThostFtdcMdApi.h>
#include <ctp-traderAPI/ThostFtdcUserApiStruct.h>
#include <ctp-traderAPI/ThostFtdcUserApiDataType.h>

namespace quote
{

class ctp : public CThostFtdcMdSpi, public CThostFtdcMdApi
{
public:
    ctp() : _mdapi{nullptr} {}
    ~ctp() {}

public:
    void connect(const int port, 
                 const char* ip, 
                 const char* psz_flow_path = "", 
                 const bool is_using_udp = false, 
                 const bool is_multicast = false);
    void login(unsigned int retry_times = 1, unsigned int retry_interval_ms = 1000);
    bool subscribe(char** instruments);

public:
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) override;

private:
    CThostFtdcMdApi* _mdapi;
};
    
}

#endif