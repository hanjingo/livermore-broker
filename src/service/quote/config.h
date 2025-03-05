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

    std::string ctp_ip;
    int ctp_port;
    std::string ctp_flow_md_path;
    bool ctp_using_udp;
    bool ctp_multicast;
    std::vector<std::string> ctp_instruments;
};

}

#endif