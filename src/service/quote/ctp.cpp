#include "ctp.h"

namespace quote
{

void ctp::connect(const int port, const char* ip, const char* psz_flow_path, const bool is_using_udp, const bool is_multicast)
{
    _mdapi = CThostFtdcMdApi::CreateFtdcMdApi(psz_flow_path, is_using_udp, is_multicast);
    _mdapi->RegisterSpi(this);
    if (!is_using_udp)
    {
        _mdapi->RegisterFront(libcpp::string_util::fmt("tcp://{0}:{1}", ip, port).c_str());
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
    // ///交易日
	// TThostFtdcDateType	TradingDay;
	// ///合约代码
	// TThostFtdcInstrumentIDType	InstrumentID;
	// ///交易所代码
	// TThostFtdcExchangeIDType	ExchangeID;
	// ///合约在交易所的代码
	// TThostFtdcExchangeInstIDType	ExchangeInstID;
	// ///最新价
	// TThostFtdcPriceType	LastPrice;
	// ///上次结算价
	// TThostFtdcPriceType	PreSettlementPrice;
	// ///昨收盘
	// TThostFtdcPriceType	PreClosePrice;
	// ///昨持仓量
	// TThostFtdcLargeVolumeType	PreOpenInterest;
	// ///今开盘
	// TThostFtdcPriceType	OpenPrice;
	// ///最高价
	// TThostFtdcPriceType	HighestPrice;
	// ///最低价
	// TThostFtdcPriceType	LowestPrice;
	// ///数量
	// TThostFtdcVolumeType	Volume;
	// ///成交金额
	// TThostFtdcMoneyType	Turnover;
	// ///持仓量
	// TThostFtdcLargeVolumeType	OpenInterest;
	// ///今收盘
	// TThostFtdcPriceType	ClosePrice;
	// ///本次结算价
	// TThostFtdcPriceType	SettlementPrice;
	// ///涨停板价
	// TThostFtdcPriceType	UpperLimitPrice;
	// ///跌停板价
	// TThostFtdcPriceType	LowerLimitPrice;
	// ///昨虚实度
	// TThostFtdcRatioType	PreDelta;
	// ///今虚实度
	// TThostFtdcRatioType	CurrDelta;
	// ///最后修改时间
	// TThostFtdcTimeType	UpdateTime;
	// ///最后修改毫秒
	// TThostFtdcMillisecType	UpdateMillisec;
	// ///申买价一
	// TThostFtdcPriceType	BidPrice1;
	// ///申买量一
	// TThostFtdcVolumeType	BidVolume1;
	// ///申卖价一
	// TThostFtdcPriceType	AskPrice1;
	// ///申卖量一
	// TThostFtdcVolumeType	AskVolume1;
	// ///申买价二
	// TThostFtdcPriceType	BidPrice2;
	// ///申买量二
	// TThostFtdcVolumeType	BidVolume2;
	// ///申卖价二
	// TThostFtdcPriceType	AskPrice2;
	// ///申卖量二
	// TThostFtdcVolumeType	AskVolume2;
	// ///申买价三
	// TThostFtdcPriceType	BidPrice3;
	// ///申买量三
	// TThostFtdcVolumeType	BidVolume3;
	// ///申卖价三
	// TThostFtdcPriceType	AskPrice3;
	// ///申卖量三
	// TThostFtdcVolumeType	AskVolume3;
	// ///申买价四
	// TThostFtdcPriceType	BidPrice4;
	// ///申买量四
	// TThostFtdcVolumeType	BidVolume4;
	// ///申卖价四
	// TThostFtdcPriceType	AskPrice4;
	// ///申卖量四
	// TThostFtdcVolumeType	AskVolume4;
	// ///申买价五
	// TThostFtdcPriceType	BidPrice5;
	// ///申买量五
	// TThostFtdcVolumeType	BidVolume5;
	// ///申卖价五
	// TThostFtdcPriceType	AskPrice5;
	// ///申卖量五
	// TThostFtdcVolumeType	AskVolume5;
	// ///当日均价
	// TThostFtdcPriceType	AveragePrice;
	// ///业务日期
	// TThostFtdcDateType	ActionDay;
	// ///熔断参考价
	// TThostFtdcPriceType	CircuitRefPrice;
	// ///行情发送时间
	// TThostFtdcSendingTimeType	SendingTime;
	// ///成交量（long long）
	// TThostFtdcBigVolumeType	BigVolume;

    
    // TODO dispatch task
    LOG_DEBUG("");
}

}