#ifndef CONFIG_MGR_H
#define CONFIG_MGR_H

#include <string>
#include <chrono>
#include <libcpp/log/logger.hpp>
#include <libcpp/encoding/ini.hpp>
#include <libcpp/io/file.hpp>
#include <libcpp/strings/string.hpp>

#include "error.h"
#include "version.h"

namespace quote
{

struct config_mgr
{
    config_mgr() = delete;
    config_mgr(const config_mgr&) = delete;
    config_mgr& operator=(const config_mgr&) = delete;

    static void clear();
    static error load(const char* filepath);
    static error check();

    static std::string log_path;
    static FSIZE log_size;
    static int log_file_num;
    static bool log_rotate_on_open;
    static libcpp::log_lvl log_min_lvl;

    static std::string crash_path;
};

}

#endif