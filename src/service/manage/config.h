#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>
#include <chrono>

#include "error.h"
#include "version.h"
#include "config_base.h"

namespace manage
{

struct config : public common::config_base
{
    config() : common::config_base() {}
    ~config() {};

    void clear() override;
    err_t load(const char* filepath) override;
    err_t check() override;

    std::chrono::milliseconds serv_scan_dur;
    std::vector<std::string> services;
};

}

#endif