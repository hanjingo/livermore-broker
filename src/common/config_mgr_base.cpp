#include "config_mgr_base.h"

namespace common
{

config_mgr_base& config_mgr_base::instance()
{
    static config_mgr_base inst;
    return inst;
}

void config_mgr_base::clear()
{
    log_path = "";
    log_size = MB(0);
    log_file_num = 0;
    log_rotate_on_open = false;
    log_min_lvl = libcpp::log_lvl_trace;
    crash_path = "";
}

err_t config_mgr_base::load(const char* filepath)
{
    LOG_DEBUG("load file:{}", filepath);
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

    return check();
}

err_t config_mgr_base::check()
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
    if (log_min_lvl > libcpp::log_lvl_critial)
        return error::log_lvl_too_big;
    // TODO check crash path

    return error::ok;
}

}