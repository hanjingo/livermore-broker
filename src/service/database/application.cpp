#include "application.h"

#include <libcpp/io/filepath.hpp>
#include <libcpp/os/env.h>

namespace database
{

application& application::instance()
{
    static application inst;
    return inst;
}    

err_t application::init(const char* id)
{
    LOG_DEBUG("database application::init() enter");
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
    LOG_DEBUG("database application::run() enter");

    // run tcp gates
    while (true)
    {
        // TODO
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return error::ok;
}

err_t application::stop()
{
    // TODO

    common::application_base::stop();
    return error::ok;
}

}