#include "application_base.h"

namespace common
{

application_base& application_base::instance()
{
    static application_base inst;
    return inst;
}    

err_t application_base::init()
{
    // load cofig
    auto err = config_mgr_base::instance().load("livermore-broker.ini");
    if (err != error::ok)
        return err;

    // add log
    libcpp::logger::instance()->add_sink(
        libcpp::logger::create_rotate_file_sink(
            config_mgr_base::instance().log_path, 
            config_mgr_base::instance().log_size, 
            config_mgr_base::instance().log_file_num, 
            config_mgr_base::instance().log_rotate_on_open));
    libcpp::logger::instance()->set_level(config_mgr_base::instance().log_min_lvl);

    // ignore signal
    libcpp::sigcatch({SIGABRT, SIGTERM}, [](int sig){});

    // add crash handler
    libcpp::crash_handler::instance()->prevent_set_unhandled_exception_filter();
    libcpp::crash_handler::instance()->set_local_path(config_mgr_base::instance().crash_path);
    LOG_DEBUG("livermore-broker crash set local path={}", config_mgr_base::instance().crash_path);

    return error::ok;
}

err_t application_base::run()
{
    while (true) { LOG_DEBUG("service running..."); libcpp::application::msleep(500); }
    return error::ok;
}

err_t application_base::stop()
{
    return error::ok;
}

}