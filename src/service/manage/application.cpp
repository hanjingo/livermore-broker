#include "application.h"

#include <libcpp/os/env.h>

namespace manage
{

application& application::instance()
{
    static application inst;
    return inst;
}    

err_t application::init(const char* id)
{
    LOG_DEBUG("manage application::init() enter");

    // load our config
    conf.name = std::string(id);
    err_t err = conf.load("livermore-broker.ini");
    if (err != error::ok)
        return err;

    // super init
    err = common::application_base::init(conf);
    if (err != error::ok)
        return err;

    return error::ok;
}

err_t application::run()
{
    LOG_DEBUG("manage run() enter");
    err_t err = error::ok;
    // add watch list
    for (auto serv : conf.services)
    {
        if (serv.empty())
        {
            LOG_WARN("skip run service with serv={}", serv);
            continue;
        }

        LOG_DEBUG("create service with serv={}", serv);
        proc p{serv};
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