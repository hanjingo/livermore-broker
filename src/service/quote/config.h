#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>

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
    bool xtp_auto_save;
    int xtp_client_id;
    int xtp_account_count;
    std::string xtp_account_key;
    int xtp_resume_type;
    std::string xtp_filepath;
    bool xtp_ping_pong_test;
    int xtp_heatbeat_interval;
    int xtp_buf_size;
    int xtp_sdk_log_lvl;
};

}

#endif