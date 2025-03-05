#ifndef CONFIG_BASE_H
#define CONFIG_BASE_H

#include <string>
#include <libcpp/log/logger.hpp>

#include "error_base.h"
#include "config_base.h"

namespace common
{

struct config_base
{
    config_base() {};
    ~config_base() {};

    virtual void clear();
    virtual err_t load(const char* filepath);
    virtual err_t check();

    std::string module;

    std::string log_path;
    unsigned long long log_size;
    int log_file_num;
    bool log_rotate_on_open;
    libcpp::log_lvl log_min_lvl;

    std::string crash_path;
};

}

#endif