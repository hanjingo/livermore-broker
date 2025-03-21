#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>
#include <unordered_map>

#include "error.h"
#include "version.h"
#include "config_base.h"

namespace quote
{

struct config : public common::config_base
{
    config() : common::config_base() {};
    ~config() {};

    void clear() override;
    err_t load(const char* filepath) override;
    err_t check() override;

    bool ctp_enable = false;
    std::vector<std::string> ctp_addrs;
    std::string ctp_flow_md_path;
    bool ctp_using_udp;
    bool ctp_multicast;
    std::vector<std::string> ctp_instruments;

    bool xtp_enable = false;
    std::vector<std::string> xtp_addrs;
    std::string xtp_username;
    std::string xtp_passwd;
    bool xtp_using_udp;
    std::string xtp_local_ip;
    bool xtp_auto_save;
    int xtp_client_id;
    int xtp_account_count;
    std::string xtp_account_key;
    int xtp_resume_type;
    std::string xtp_filepath;
    bool xtp_ping_pong_test;
    int xtp_heatbeat_interval;
    int xtp_buf_size_mb;
    int xtp_sdk_log_lvl;
    std::unordered_map<int, std::vector<std::string> > xtp_instruments;

    bool tx_enable = false;
    std::vector<std::string> tx_instruments;
};

}

#endif