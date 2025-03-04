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
    config_mgr::instance().module = MODULE;
    auto err = config_mgr::init();
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
    if (!libcpp::file_path::make_dir(config_mgr::instance().flow_md_path))
    {
        LOG_ERROR("make flow_md_path={0} fail", config_mgr::instance().flow_md_path);
        return error::create_flow_md_path_fail;
    }

    return error::ok;
}

err_t application::run()
{
    
}

}