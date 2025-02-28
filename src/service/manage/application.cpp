#include "application.h"

namespace manage
{

application& application::instance()
{
    static application inst;
    return inst;
}    

err_t application::init()
{
    LOG_DEBUG("init() enter");
    // super init
    common::config_mgr_base::instance().module = MODULE;
    auto err = common::application_base::init();
    if (err != error::ok)
        return err;

    // load our config
    err = config_mgr::instance().load("livermore-broker.ini");
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
    LOG_DEBUG("run() enter");
    err_t err = error::ok;
    // add watch list
    for (std::string serv : config_mgr::instance().services)
    {
        proc p{serv};
        LOG_DEBUG("create service:{}", serv);
        err = p.run(true);
        if (err != error::ok)
            return err;

        err = proc_mgr::instance().add_watch_list(std::move(p));
        if (err != error::ok)
            return err;
    }

    return proc_mgr::instance().watch();
}

err_t application::stop()
{
    return error::ok;
}

}