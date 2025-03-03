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
    LOG_DEBUG("application::init() enter");
    common::config_mgr_base::instance().module = MODULE;
    auto err = common::application_base::init();
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

    // mkdir
    

    return error::ok;
}

}