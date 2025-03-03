#include "ctp.h"

namespace quote
{

void ctp::connect(const int port, const char* ip, const char* psz_flow_path, const bool is_using_udp, const bool is_multicast)
{
    _mdapi = CThostFtdcMdApi::CreateFtdcMdApi(psz_flow_path, is_using_udp, is_multicast);
    _mdapi->RegisterSpi(this);
    if (!is_using_udp)
    {
        char ip_port[27] = {0};
        sprintf(ip_port, "tcp://%s:%d", ip, port);
        _mdapi->RegisterFront(ip_port);
    } else {
        // TODO
    }
    _mdapi->Init();
}

void ctp::login(unsigned int retry_times, unsigned int retry_interval_ms)
{
    std::chrono::milliseconds dur{retry_interval_ms};
    CThostFtdcReqUserLoginField field = {0};
    while(retry_times != 0)
    {
        if (_mdapi->ReqUserLogin(&field, 1) == 0)
            return;

        retry_times--;
        std::this_thread::sleep_for(dur);
    }
}

bool ctp::subscribe(char** instruments)
{
    return _mdapi->SubscribeMarketData(instruments, 1) == 0;
}


void ctp::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    // TODO
}

}