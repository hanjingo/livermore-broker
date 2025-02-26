#include "config_mgr.h"

namespace manage
{

void config_mgr::clear()
{
    log_path = "";
    log_size = MB(0);
    log_file_num = 0;
    log_rotate_on_open = false;
    log_min_lvl = libcpp::log_lvl_trace;
    crash_path = "";
    serv_scan_dur = std::chrono::milliseconds(0);
    services.clear();
}

error config_mgr::load(const char* filepath)
{
    clear();

    // parse config
    libcpp::ini file;
    if (!file.read_file(filepath))
        return error::read_config_fail;

    auto cfg = file.get_child(MODULE);
    log_path = cfg.get<std::string>("log_path");
    log_size = MB(cfg.get<int>("log_file_size_mb"));
    log_file_num = cfg.get<int>("log_file_num");
    log_rotate_on_open = cfg.get<bool>("log_file_rotate_on_open");
    log_min_lvl = static_cast<libcpp::log_lvl>(cfg.get<int>("log_min_lvl", 1));
    crash_path = cfg.get<std::string>("crash_path");
    serv_scan_dur = std::chrono::milliseconds(cfg.get<int>("service_scan_dur_ms"));
    std::string serv_array = cfg.get<std::string>("service_array");
    services = libcpp::string::split(serv_array, ",");

    return check();
}

error config_mgr::check()
{
    if (log_size < MB(1))
        return error::log_file_size_too_small;
    if (log_size > MB(1024))
        return error::log_file_size_too_big;
    if (log_file_num < 1)
        return error::log_file_num_too_small;
    if (log_file_num > 1024)
        return error::log_file_num_too_big;
    if (log_min_lvl < libcpp::log_lvl_trace)
        return error::log_lvl_too_small;
    if (log_min_lvl < libcpp::log_lvl_critial)
        return error::log_lvl_too_big;
    // TODO check crash path
    if (serv_scan_dur < std::chrono::milliseconds(10))
        return error::serv_scan_too_busy;
    if (serv_scan_dur > std::chrono::minutes(60))
        return error::serv_scan_too_slow;
    if (services.size() > 1024)
        return error::serv_proc_too_much;

    return error::ok;
}

}