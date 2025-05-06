#include "ctp.h"
#include "string.h"

#include <libcpp/log/logger.hpp>
#include <libcpp/util/defer.hpp>

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

error ctp::init(const char* psz_flow_path, const bool is_using_udp, const bool is_multicast)
{
	_mdapi = CThostFtdcMdApi::CreateFtdcMdApi(psz_flow_path, is_using_udp, is_multicast);
	if (_mdapi == nullptr)
		return error::ctp_create_mdapi_fail;

	_mdapi->RegisterSpi(this);
	return error::ok;
}

error ctp::connect(const std::vector<std::string>& addrs, unsigned int timeout_ms)
{
	if (status_change(stat::connecting) != stat::connecting)
		return error::ctp_current_status_not_allowed_connect;

	if (addrs.empty())
		return error::ctp_addr_empty;

	for (auto addr : addrs)
		_mdapi->RegisterFront(const_cast<char*>(addr.c_str()));

	_mdapi->Init();
	if (timeout_ms < 0)
	{
		_mdapi->Join();
		return error::ok;
	}

	while (timeout_ms > 0)
	{
		if (status() == stat::connected)
			return error::ok;

		timeout_ms--;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	return error::ctp_connect_timeout;
}

error ctp::login(unsigned int retry_times, unsigned int retry_interval_ms)
{
	if (retry_times < 1)
		return error::ctp_request_user_login_timeout;

	retry_times--;
	if (status_change(stat::logging) != stat::logging)
	{
		return error::ctp_current_status_not_allowed_login;
	}

    CThostFtdcReqUserLoginField field = {0};
	if (_mdapi->ReqUserLogin(&field, req_id()) != 0)
	{
		return error::ctp_request_user_login_fail;
	}

	return error::ok;
}

error ctp::logout()
{
	if (status_change(stat::logging_out) != stat::logging_out)
		return error::ctp_current_status_not_allowed_logging_out;

	return error::ok;
}

error ctp::subscribe_market_data(const std::vector<std::string>& instruments)
{	
	char* topics[INSTRUMENT_LEN];
	int row = 0;
	for (auto id : instruments) 
	{
		if (_md_topics.find(id) != _md_topics.end())
			continue;

		_md_topics.emplace(id);
		topics[row++] = new char[INSTRUMENT_LEN];
		memcpy(topics[row], id.c_str(), INSTRUMENT_LEN);
	}

	int ret = _mdapi->SubscribeMarketData(topics, row);

	for (int i = 0; i < row; ++i)
		delete topics[i];

	switch (ret)
	{
	case 0: return error::ok;
	case -1: return error::ctp_disconnected;
	case -2: return error::ctp_too_much_unhandled_request;
	case -3: return error::ctp_too_much_request;
	default: return error::ctp_unknow_error;
	}
}

error ctp::unsubscribe_market_data(const std::vector<std::string>& instruments)
{
	char* topics[INSTRUMENT_LEN];
	int row = 0;
	for (auto id : instruments) 
	{
		if (_md_topics.find(id) != _md_topics.end())
			continue;

		_md_topics.erase(id);
		topics[row++] = new char[INSTRUMENT_LEN];
		memcpy(topics[row], id.c_str(), INSTRUMENT_LEN);
	}

	int ret = _mdapi->UnSubscribeMarketData(topics, row);
	switch (ret)
	{
	case 0: return error::ok;
	case -1: return error::ctp_disconnected;
	case -2: return error::ctp_too_much_unhandled_request;
	case -3: return error::ctp_too_much_request;
	default: return error::ctp_unknow_error;
	}
}

error ctp::wait()
{
	// run thread, wait msg
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return error::ok;
}


///////////////////////////// callback function ///////////////////////////////////////
void ctp::OnFrontConnected()
{
	if (status_change(stat::connected) != stat::connected)
	{
		LOG_ERROR("ctp connected stat change fail");
		return;
	}
	
	LOG_INFO("ctp connected");
}

void ctp::OnFrontDisconnected(int nReason)
{
	if (status_change(stat::disconnected) != stat::disconnected)
	{
		LOG_ERROR("ctp disconnected stat change fail");
		return;
	}
	
	LOG_INFO("ctp disconnected with nReason={}", common::err_to_hex(nReason));
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