#include "xtp.h"

namespace quote
{

xtp::stat xtp::status_change(const stat new_stat)
{
	xtp::stat old_stat = _stat.load();
	switch (new_stat)
	{
		case stat::logging: { 
			if (old_stat != stat::logged_out)
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
        case stat::logged_out: { 
			if (old_stat != stat::logging_out)
				return old_stat;
			break;
		}
		default: return old_stat;
	}
	
	return _stat.compare_exchange_weak(old_stat, new_stat) ? new_stat : old_stat;
}

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

error xtp::register_addr(
    const std::vector<std::string>& addrs = {}, 
    bool using_udp = false,
    const char* local_ip = NULL)
{
    if (addrs.empty())
		return error::xtp_addr_empty;

    for (int i = 0; i < addrs.size() && i < XTP_ADDR_N; ++i)
    {
        auto tmp = libcpp::string_util::split(addrs[i], ":");
        if (tmp.size() < 2)
            return error::xtp_addr_invalid;

        _addrs[i] = std::pair<const char*, uint16_t>(tmp[0].c_str(), std::stoi(tmp[1]));
    }

    _protocol = (using_udp) ? XTP_PROTOCOL_UDP : XTP_PROTOCOL_TCP;
    _local_ip = std::string(local_ip);
}

error xtp::login(
    const char* user, 
    const char* password, 
    uint32_t timeout_ms)
{
    if (status_change(stat::logging) != stat::logging)
		return error::xtp_current_status_not_allowed_login;

    auto err = error::ok;
    for (int i = 0; i < XTP_ADDR_N; ++i)
    {
        auto ret = _api->Login(
            _addrs[i].first, _addrs[i].second, user, password, _protocol, _local_ip.c_str());
        
        switch (ret)
        {
            case 0: err = error:ok; break;
            case -1: err = error::xtp_connect_serv_fail; break;
            case -2: err = error::xtp_connect_already_exist; break;
            case -3: err = error::xtp_input_error; break;
            default: err = xtp_unknow_error; break;
        }

        if (err == error::ok)
            break;
    }

    return (i == XTP_ADDR_N) ? error::xtp_login_fail : error::ok;
}

/////////////////////////////////// callback function /////////////////////////////////////////

void xtp::OnDisconnected(int reason)
{
    if (status_change(stat::logged_out) != stat::logged_out)
	{
		LOG_ERROR("xtp logged out stat change fail");
		return;
	}
	
	LOG_INFO("xtp disconnected with reason={}", common::err_to_hex(reason));
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