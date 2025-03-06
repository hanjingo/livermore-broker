#include "application.h"

#include <libcpp/os/env.h>

namespace manage
{

application& application::instance()
{
    static application inst;
    return inst;
}    

err_t application::init()
{
    LOG_DEBUG("manage application::init() enter");
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
    LOG_INFO("livermore-manage");
    LOG_INFO("livermore-manage {}.{}.{}", 
        MANAGE_MAJOR_VERSION, 
        MANAGE_MINOR_VERSION, 
        MANAGE_PATCH_VERSION);
    LOG_INFO("livermore-manage compile time {}", COMPILE_TIME);
    LOG_INFO("livermore-manage email {}", "hehehunanchina@live.com");
    return error::ok;
}

err_t application::run()
{
    LOG_DEBUG("manage run() enter");
    err_t err = error::ok;
    // add watch list
    for (std::string serv : conf.services)
    {
        proc p{serv};
        LOG_DEBUG("create service:{}", serv);
        err = p.run(true);
        if (err != error::ok)
            return err;

        err = procs.add_watch_list(std::move(p));
        if (err != error::ok)
            return err;
    }

    return procs.watch(conf.serv_scan_dur);
}

}