#include "application.h"

namespace manage
{

error application::init()
{
    // load cofig
    auto err = config_mgr::load("livermore-broker.ini");
    if (err != error::ok)
        return err;

    // add log
    libcpp::logger::instance()->add_sink(
        libcpp::logger::create_sink(
            config_mgr::log_path, 
            config_mgr::log_size, 
            config_mgr::log_file_num, 
            config_mgr::log_rotate_on_open));
    libcpp::logger::instance()->set_level(config_mgr::log_min_lvl);

    // add water mark
    LOG_INFO("livermore-manage {}", MODULE);
    LOG_INFO("livermore-manage {}.{}.{}", 
        MANAGE_MAJOR_VERSION, 
        MANAGE_MINOR_VERSION, 
        MANAGE_PATCH_VERSION);
    LOG_INFO("livermore-manage compile time {}", COMPILE_TIME);
    LOG_INFO("livermore-manage author {}", "hehehunanchina@live.com");

    // ignore signal
    libcpp::sigcatch({SIGABRT, SIGTERM}, [](int sig){});

    // add crash handler
    libcpp::crash_handler::instance()->prevent_set_unhandled_exception_filter();
    libcpp::crash_handler::instance()->set_local_path(config_mgr::crash_path);
    LOG_DEBUG("livermore-broker crash set local path={}", config_mgr::crash_path);

    return error::ok;
}

error application::run()
{
    return error::ok;
}

error application::stop()
{
    return error::ok;
}

}