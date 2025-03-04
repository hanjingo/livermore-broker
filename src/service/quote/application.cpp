#include "application.h"

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

    // // mkdir ctp file dir
    // if (!libcpp::file_path::make_dir(conf..ctp_flow_md_path))
    // {
    //     LOG_ERROR("make flow_md_path={0} fail", conf..ctp_flow_md_path);
    //     return error::ctp_create_flow_md_path_fail;
    // }

    return error::ok;
}

err_t application::run()
{
    if (_ctp == nullptr)
        return error::ctp_null;

    _ctp->subscribe(conf..ctp_instruments);

    _ctp->connect(conf..ctp_port, 
                  conf..ctp_ip.c_str(), 
                  conf..ctp_flow_md_path.c_str(),
                  conf..ctp_using_udp,
                  conf..ctp_multicast);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return error::ok;
}

}