#include "ctp.h"

namespace quote
{

ctp::stat ctp::status_change(const stat new_stat)
{
	ctp::stat old_stat = _stat.load();
	switch (new_stat)
	{
		case stat::disconnected: { 
			if (old_stat != stat::connecting && old_stat != stat::connected)
				return old_stat;
			break;
		}
		case stat::connecting: { 
			if (old_stat != stat::disconnected)
				return old_stat;
			break;
		}
		case stat::connected: { 
			if (old_stat != stat::connecting && old_stat != stat::logging_out)
				return old_stat;
			break;
		}
		case stat::logging: { 
			if (old_stat != stat::connected)
				return old_stat;
			break; 
		}
		case stat::logged: { 
			if (old_stat != stat::logging)
				return old_stat;
			break; 
		}
		case stat::logging_out: { 
			if (old_stat != stat::logged)
				return old_stat;
			break;
		}
		default: return old_stat;
	}
	

	return _stat.compare_exchange_weak(old_stat, new_stat) ? new_stat : old_stat;
}

error ctp::connect(const int port, 
				   const char* ip, 
				   const char* psz_flow_path, 
				   const bool is_using_udp, 
				   const bool is_multicast,
				   const unsigned int timeout_dur_ms)
{
	if (status_change(stat::connecting) != stat::connecting)
		return error::ctp_current_status_not_allowed_connect;

    _mdapi = CThostFtdcMdApi::CreateFtdcMdApi(psz_flow_path, is_using_udp, is_multicast);
    _mdapi->RegisterSpi(this);
    if (!is_using_udp)
    {
		char addr[27] = {0};
        sprintf(addr, "tcp://%s:%d", ip, port);
        _mdapi->RegisterFront(addr);
    } else {
        // TODO
    }
    _mdapi->Init(); // return by OnFrontConnected

	return error::ok;
}

error ctp::login(unsigned int retry_times, unsigned int retry_interval_ms)
{
	if (status_change(stat::logging) != stat::logging)
		return error::ctp_current_status_not_allowed_login;

	_login_retry_times = retry_times;
	_login_retry_interval_ms = retry_interval_ms;
    std::chrono::milliseconds dur{retry_interval_ms};
    CThostFtdcReqUserLoginField field = {0};
	if (_mdapi->ReqUserLogin(&field, _request_id) != 0)
		return error::ctp_request_user_login_fail;

	return error::ok;
}

error ctp::logout()
{
	if (status_change(stat::logging_out) != stat::logging_out)
		return error::ctp_current_status_not_allowed_logging_out;

	return error::ok;
}

error ctp::subscribe(const std::vector<std::string>& instruments)
{
	if (!instruments.empty())
	{
		for (auto e : instruments) 
		{
			_instruments[_instruments_row++] = new char[7];
			memcpy(_instruments[_instruments_row], e.c_str(), 7);
		}
	}
	
    if (status() != stat::logged) 
		return error::ok;
	_mdapi->SubscribeMarketData(_instruments, _request_id);
	return error::ok;
}

void ctp::OnFrontConnected()
{
	if (status_change(stat::connected) != stat::connected)
		LOG_ERROR("ctp connected stat change fail");
	else
		LOG_INFO("ctp connected");

	login();
}

void ctp::OnFrontDisconnected(int nReason)
{
	if (status_change(stat::disconnected) != stat::disconnected)
		LOG_ERROR("ctp disconnected stat change fail");
	else
		LOG_INFO("ctp disconnected");
}

void ctp::OnHeartBeatWarning(int nTimeLapse)
{
	LOG_WARN("heartbeat timeout with nTimeLapse={}", nTimeLapse);
}

void ctp::OnRspUserLogin(
    CThostFtdcRspUserLoginField *pRspUserLogin, 
    CThostFtdcRspInfoField *pRspInfo, 
    int nRequestID, 
    bool bIsLast)
{
	_login_retry_times--;
	if (pRspInfo->ErrorID != 0)
	{
		LOG_ERROR("login fail with pRspInfo->ErrorID={0}", pRspInfo->ErrorID);
		return;
	}

	if (status_change(stat::logged) != stat::logged)
	{
		LOG_ERROR("current status not allowed login");
		return;
	}

	subscribe();
	LOG_INFO("login success");
}
    
void ctp::OnRspUserLogout(
	CThostFtdcUserLogoutField *pUserLogout, 
    CThostFtdcRspInfoField *pRspInfo, 
    int nRequestID, 
    bool bIsLast)
{
	LOG_DEBUG("OnRspUserLogout");
}

void ctp::OnRspError(
    CThostFtdcRspInfoField *pRspInfo, 
    int nRequestID, 
    bool bIsLast)
{
	LOG_DEBUG("OnRspError");
}

void ctp::OnRspSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
    CThostFtdcRspInfoField *pRspInfo, 
    int nRequestID, 
    bool bIsLast)
{
	LOG_DEBUG("OnRspSubMarketData");
}

void ctp::OnRspUnSubMarketData(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
    CThostFtdcRspInfoField *pRspInfo, 
    int nRequestID, 
    bool bIsLast)
{
	LOG_DEBUG("OnRspUnSubMarketData");
}

void ctp::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	LOG_DEBUG("OnRtnDepthMarketData");
}
    
void ctp::OnRspSubForQuoteRsp(
    CThostFtdcSpecificInstrumentField *pSpecificInstrument, 
    CThostFtdcRspInfoField *pRspInfo, 
    int nRequestID, 
    bool bIsLast)
{
	LOG_DEBUG("OnRspSubForQuoteRsp");
}

void ctp::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
	LOG_DEBUG("OnRtnForQuoteRsp");
}

}