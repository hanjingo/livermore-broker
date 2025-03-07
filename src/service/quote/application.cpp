#include "application.h"

#include <libcpp/io/filepath.hpp>
#include <libcpp/os/env.h>

namespace quote
{

application& application::instance()
{
    static application inst;
    return inst;
}    

err_t application::init()
{
    LOG_DEBUG("quote application::init() enter");
    // load our config
    conf.module = MODULE;
    err_t err = conf.load("livermore-broker.ini");
    if (err != error::ok)
        return err;

    // super init
    err = common::application_base::init(conf);
    if (err != error::ok)
        return err;

    // add water mark
    LOG_INFO("livermore-quote");
    LOG_INFO("livermore-quote {}.{}.{}", 
        QUOTE_MAJOR_VERSION, 
        QUOTE_MINOR_VERSION, 
        QUOTE_PATCH_VERSION);
    LOG_INFO("livermore-quote compile time {}", COMPILE_TIME);
    LOG_INFO("livermore-quote email {}", "hehehunanchina@live.com");

    // mkdir ctp file dir
    if (!libcpp::file_path::is_exist(conf.ctp_flow_md_path) && 
            !libcpp::file_path::make_dir(conf.ctp_flow_md_path))
    {
        LOG_ERROR("make flow_md_path={0} fail", conf.ctp_flow_md_path);
        return error::ctp_create_flow_md_path_fail;
    }

    // init ctp obj
    if (conf.ctp_enable)
    {
        auto ctp_obj = new ctp();
        err = ctp_obj->init(conf.ctp_flow_md_path.c_str(), conf.ctp_using_udp, conf.ctp_multicast);
        if (err != error::ok)
            return err;
    }

    // init xtp obj
    if (conf.xtp_enable)
    {
        auto xtp_obj = new xtp();
        err = xtp_obj->init(conf.xtp_client_id, conf.xtp_filepath.c_str(), conf.xtp_sdk_log_lvl, conf.xtp_heatbeat_interval, conf.xtp_buf_size);
        if (err != error::ok)
            return err;
    }

    return error::ok;
}

err_t application::run()
{
    LOG_DEBUG("quote application::run() enter");
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (ctp_obj != nullptr)
        {
            if (ctp_obj->status() < ctp::stat::connected)
            {
                auto err = ctp_obj->connect(conf.ctp_addrs);
                if (err != error::ok) 
                {
                    LOG_ERROR("ctp connect fail with err code={}", common::err_to_hex(err));
                    continue;
                }
                LOG_INFO("ctp connect succ");
            }

            if (ctp_obj->status() > ctp::stat::connecting && ctp_obj->status() < ctp::stat::logged)
            {
                auto err = ctp_obj->login();
                if (err != error::ok)
                {
                    LOG_ERROR("ctp login fail with err code={}", common::err_to_hex(err));
                    continue;
                }
                LOG_INFO("ctp login succ");
            }

            if (ctp_obj->status() > ctp::stat::logged)
            {
                auto err = ctp_obj->subscribe_market_data(conf.ctp_instruments);
                if (err != error::ok)
                {
                    LOG_ERROR("ctp subscribe fail with err code={}", common::err_to_hex(err));
                    continue;
                }
            }

            ctp_obj->wait();
        }

        if (xtp_obj != nullptr)
        {
            if (xtp_obj->status() == xtp::stat::logged_out)
            {
                auto err = xtp_obj->login(conf.xtp_username.c_str(), conf.xtp_passwd.c_str());
                if (err != error::ok)
                {
                    LOG_ERROR("xtp login fail with err code={}", common::err_to_hex(err));
                    continue;
                }
                LOG_INFO("xtp login succ");
            }
        }
    }
    return error::ok;
}

}