#include "config_mgr.h"

namespace manage
{

config_mgr& config_mgr::instance()
{
    static config_mgr inst;
    return inst;
}

void config_mgr::clear()
{
    config_mgr_base::clear();
    serv_scan_dur = std::chrono::milliseconds(0);
    services.clear();
}

err_t config_mgr::load(const char* filepath)
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
    serv_scan_dur = std::chrono::milliseconds(cfg.get<int>("service_scan_dur_ms"));
    std::string serv_array = cfg.get<std::string>("service_array");
    services = libcpp::string_util::split(serv_array, ",");

    return check();
}

err_t config_mgr::check()
{
    auto err = config_mgr_base::check();
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