#include "config.h"

#include <iostream>
#include <libcpp/log/logger.hpp>
#include <libcpp/encoding/ini.hpp>
#include <libcpp/io/file.hpp>
#include <libcpp/util/string_util.hpp>

namespace manage
{

void config::clear()
{
    common::config_base::clear();
    serv_scan_dur = std::chrono::milliseconds(0);
    services.clear();
}

err_t config::load(const char* filepath)
{
    clear();

    LOG_DEBUG("manage config load file {}", filepath);
    auto err = config_base::load(filepath);
    if (err != error::ok)
        return err;

    serv_scan_dur = std::chrono::milliseconds(cfg.get<int>("service_scan_dur_ms"));
    std::string serv_array = cfg.get<std::string>("service_array");
    auto servs = libcpp::string_util::split(serv_array, ",");
    for (auto serv : servs)
    {
        if (serv.empty())
            continue;

        services.push_back(serv);
    }
    return check();
}

err_t config::check()
{
    auto err = common::config_base::check();
    if (err != error::ok)
        return err;
    if (serv_scan_dur < std::chrono::milliseconds(10))
        return error::serv_scan_too_busy;
    if (serv_scan_dur > std::chrono::minutes(60))
        return error::serv_scan_too_slow;
    if (services.size() > 1024)
        return error::serv_proc_too_much;

    return error::ok;
}

}