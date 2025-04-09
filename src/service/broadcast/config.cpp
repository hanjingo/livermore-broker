#include "config.h"

#include <chrono>
#include <libcpp/log/logger.hpp>
#include <libcpp/encoding/ini.hpp>
#include <libcpp/io/file.hpp>
#include <libcpp/util/string_util.hpp>

namespace broadcast
{

void config::clear()
{
    config_base::clear();
    
}

err_t config::load(const char* filepath)
{
    clear();

    LOG_INFO("load file {}", filepath);
    // parse config
    libcpp::ini file;
    if (!file.read_file(filepath))
        return common::error::read_config_fail;

    auto cfg = file.get_child(MODULE);
    log_path = cfg.get<std::string>("log_path");
    log_size = MB(cfg.get<int>("log_file_size_mb"));
    log_file_num = cfg.get<int>("log_file_num");
    log_rotate_on_open = cfg.get<bool>("log_file_rotate_on_open");
    log_min_lvl = static_cast<libcpp::log_lvl>(cfg.get<int>("log_min_lvl", 1));
    crash_path = cfg.get<std::string>("crash_path");

    auto vec = libcpp::string_util::split(cfg.get<std::string>("tcp_ports"), ",");
    for (auto e : vec)
    {
        tcp_ports.push_back(static_cast<std::uint16_t>(std::stoi(e)));
    }
    vec = libcpp::string_util::split(cfg.get<std::string>("bind_cpu_cores"), ",");
    for (auto e : vec)
    {
        cpu_cores.push_back(static_cast<std::uint16_t>(std::stoi(e)));
    }
    
    return check();
}

err_t config::check()
{
    auto err = config_base::check();
    if (err != error::ok)
        return err;

    return error::ok;
}

}