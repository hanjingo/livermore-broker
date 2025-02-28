#ifndef CONFIG_MGR_BASE_H
#define CONFIG_MGR_BASE_H

#include <string>
#include <chrono>
#include <libcpp/log/logger.hpp>
#include <libcpp/encoding/ini.hpp>
#include <libcpp/io/file.hpp>
#include <libcpp/util/string_util.hpp>

#include "error_base.h"

namespace common
{

struct config_mgr_base
{
    config_mgr_base() {};
    ~config_mgr_base() {};
    config_mgr_base(const config_mgr_base&) = delete;
    config_mgr_base& operator=(const config_mgr_base&) = delete;

    static config_mgr_base& instance();

    virtual void clear();
    virtual err_t load(const char* filepath);
    virtual err_t check();

    std::string module;

    std::string log_path;
    FSIZE log_size;
    int log_file_num;
    bool log_rotate_on_open;
    libcpp::log_lvl log_min_lvl;

    std::string crash_path;
};

}

#endif