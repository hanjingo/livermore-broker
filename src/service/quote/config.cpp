#include "config.h"

namespace quote
{

void config::clear()
{
    config_base::clear();
    ctp_ip.clear();
    ctp_port = 0;
    ctp_flow_md_path.clear();
    ctp_using_udp = false;
    ctp_multicast = false;
    ctp_instruments.clear();
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

    ctp_ip = cfg.get<std::string>("ctp_ip");
    ctp_port = cfg.get<int>("ctp_port");
    ctp_flow_md_path = cfg.get<std::string>("ctp_flow_md_path");
    ctp_using_udp = cfg.get<bool>("ctp_using_udp");
    ctp_multicast = cfg.get<bool>("ctp_multicast");
    ctp_instruments = libcpp::string_util::split(cfg.get<std::string>("ctp_instruments"), ",");
    
    return check();
}

err_t config::check()
{
    auto err = config_base::check();
    if (err != error::ok)
        return err;
    if (ctp_ip.empty())
        return error::ctp_ip_empty;
    if (ctp_port < 0 || ctp_port > 65535)
        return ctp_port_invalid;
    if (ctp_flow_md_path.empty())
        return error::ctp_flow_md_path_empty;

    return error::ok;
}

}