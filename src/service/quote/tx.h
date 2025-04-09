#ifndef TX_H
#define TX_H

#include <vector>
#include <unordered_map>
#include <functional>

#include "error.h"
#include "market_data_shm.h"

namespace quote
{

static const char _tx_addr_base[] = "http://sqt.gtimg.cn";

class tx
{
public:
    using fn_subscribe_market_data_rsp_t = std::function<void()>;
    using fn_unsubscribe_market_data_rsp_t = std::function<void()>;
    using fn_merket_data_ntf_t = std::function<void(std::vector<common::market_data_shm*>& md)>;

public:
    tx();
    ~tx();
    error init();
    error subscribe_market_data(const std::vector<std::string>& instruments);
    error unsubscribe_market_data(const std::vector<std::string>& instruments);
    error wait(int ms = -1);

public:
    virtual void register_cb();
    virtual void on_subscribe_market_data_rsp();
    virtual void on_unsubscribe_market_data_rsp();
    virtual void on_market_data_ntf(std::vector<common::market_data_shm*>& mds);

private:
    error _query_md(int ms = 500);
    std::string _parse_id(const std::string& body);
    bool _parse_md(const std::string& body, common::market_data_shm* md);

private:
    std::string _addr = "/q=";
    std::unordered_map<std::string, common::market_data_shm*> _m_md;

    fn_subscribe_market_data_rsp_t _on_sub_rsp;
    fn_unsubscribe_market_data_rsp_t _on_unsub_rsp;
    fn_merket_data_ntf_t _on_md_ntf;
};

}

#endif