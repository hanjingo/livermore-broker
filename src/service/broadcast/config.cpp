#include "config.h"

#include <chrono>
#include <libcpp/log/logger.hpp>
#include <libcpp/encoding/ini.hpp>
#include <libcpp/io/file.hpp>
#include <libcpp/util/string_util.hpp>
#include <libcpp/hardware/cpu.h>

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
    auto err = config_base::load(filepath);
    if (err != error::ok)
        return err;

    auto vec = libcpp::string_util::split(cfg.get<std::string>("tcp_ports"), ",");
    for (auto e : vec)
    {
        if (e.empty())
            continue;

        tcp_ports.push_back(static_cast<std::uint16_t>(std::stoi(e)));
    }
    vec = libcpp::string_util::split(cfg.get<std::string>("bind_cpu_cores"), ",");
    for (auto e : vec)
    {
        if (e.empty())
            continue;

        bind_cpu_cores.push_back(static_cast<std::uint16_t>(std::stoi(e)));
    }
    msg_pool_size = cfg.get<int>("msg_pool_size");
    msg_pool_size = msg_pool_size > 0 ? msg_pool_size : 1;
    
    return check();
}

err_t config::check()
{
    auto err = config_base::check();
    if (err != error::ok)
        return err;
    for (auto core : bind_cpu_cores)
        if (core > cpu_core_num())
            return error::cpu_core_num_invalid;

    return error::ok;
}

}