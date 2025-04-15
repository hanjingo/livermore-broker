#include "config.h"

#include <chrono>
#include <libcpp/log/logger.hpp>
#include <libcpp/encoding/ini.hpp>
#include <libcpp/io/file.hpp>
#include <libcpp/util/string_util.hpp>

namespace quote
{

void config::clear()
{
    config_base::clear();
    ctp_addrs.clear();
    ctp_flow_md_path.clear();
    ctp_using_udp = false;
    ctp_multicast = false;
    ctp_instruments.clear();
}

err_t config::load(const char* filepath)
{
    clear();

    LOG_INFO("quote load file {}", filepath);
    // parse config
    auto err = config_base::load(filepath);
    if (err != error::ok)
        return err;

    ctp_enable = cfg.get<bool>("ctp_enable");
    ctp_addrs = libcpp::string_util::split(cfg.get<std::string>("ctp_addrs"), ",");
    ctp_flow_md_path = cfg.get<std::string>("ctp_flow_md_path");
    ctp_using_udp = cfg.get<bool>("ctp_using_udp");
    ctp_multicast = cfg.get<bool>("ctp_multicast");
    ctp_instruments = libcpp::string_util::split(cfg.get<std::string>("ctp_instruments"), ",");

    xtp_enable = cfg.get<bool>("xtp_enable");
    xtp_addrs=libcpp::string_util::split(cfg.get<std::string>("xtp_addrs"), ",");
    xtp_username=cfg.get<std::string>("xtp_username");
    xtp_passwd=cfg.get<std::string>("xtp_passwd");
    xtp_using_udp=cfg.get<bool>("xtp_using_udp");
    xtp_local_ip=cfg.get<std::string>("xtp_local_ip");
    xtp_auto_save=cfg.get<bool>("xtp_auto_save");
    xtp_client_id=cfg.get<int>("xtp_client_id");
    xtp_account_count=cfg.get<int>("xtp_account_count");
    xtp_account_key=cfg.get<std::string>("xtp_account_key");
    xtp_resume_type=cfg.get<int>("xtp_resume_type");
    xtp_filepath=cfg.get<std::string>("xtp_filepath");
    xtp_ping_pong_test=cfg.get<bool>("xtp_ping_pong_test");
    xtp_heatbeat_interval=cfg.get<int>("xtp_heatbeat_interval");
    xtp_buf_size_mb=cfg.get<int>("xtp_buf_size_mb");
    xtp_sdk_log_lvl=cfg.get<int>("xtp_sdk_log_lvl");
    auto vec = libcpp::string_util::split(cfg.get<std::string>("xtp_instruments"), ",");
    for (auto e : vec)
    {
        std::vector<std::string> v_elem = libcpp::string_util::split(e, ":");
        if (v_elem.size() < 2)
            continue;
        if (v_elem[0] == "SH") { xtp_instruments[1].emplace_back(v_elem[1]); }
        else if (v_elem[0] == "SZ") { xtp_instruments[2].emplace_back(v_elem[1]); }
        else if (v_elem[0] == "NQ") { xtp_instruments[3].emplace_back(v_elem[1]); }
        else{}
    }

    tx_enable = cfg.get<bool>("tx_enable");
    tx_instruments = libcpp::string_util::split(cfg.get<std::string>("tx_instruments"), ",");
    
    return check();
}

err_t config::check()
{
    auto err = config_base::check();
    if (err != error::ok)
        return err;
    if (module != MODULE)
        return common::error::conf_module_not_match;
    if (ctp_addrs.empty())
        return error::ctp_addr_empty;
    if (ctp_flow_md_path.empty())
        return error::ctp_flow_md_path_empty;

    return error::ok;
}

}