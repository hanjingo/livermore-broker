#ifndef CONFIG_MGR_H
#define CONFIG_MGR_H

#include <vector>
#include <string>
#include <chrono>
#include <libcpp/log/logger.hpp>
#include <libcpp/encoding/ini.hpp>
#include <libcpp/io/file.hpp>
#include <libcpp/util/string_util.hpp>

#include "error.h"
#include "version.h"
#include "config_mgr_base.h"

namespace manage
{

struct config_mgr : public common::config_mgr_base
{
    config_mgr() {};
    ~config_mgr() {};
    config_mgr(const config_mgr&) = delete;
    config_mgr& operator=(const config_mgr&) = delete;

    static config_mgr& instance();

    void clear();
    err_t load(const char* filepath);
    err_t check();

    std::chrono::milliseconds serv_scan_dur;
    std::vector<std::string> services;
};

}

#endif