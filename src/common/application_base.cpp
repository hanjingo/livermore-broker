#include "application_base.h"

#include <string>
#include <libcpp/log/logger.hpp>
#include <libcpp/types/singleton.hpp>
#include <libcpp/encoding/ini.hpp>
#include <libcpp/testing/crash.hpp>
#include <libcpp/testing/exception.hpp>
#include <libcpp/os/application.hpp>
#include <libcpp/os/signal.hpp>
#include <libcpp/os/dll.h>
#include <libcpp/os/env.h>
#include <libcpp/io/file.hpp>
#include <libcpp/util/string_util.hpp>

namespace common
{

err_t application_base::init(const common::config_base& config)
{
    // add log
    libcpp::logger::instance()->add_sink(
        libcpp::logger::create_rotate_file_sink(
            config.log_path, 
            config.log_size, 
            config.log_file_num, 
            config.log_rotate_on_open));
    libcpp::logger::instance()->set_level(config.log_min_lvl);

    // ignore signal
    libcpp::sigcatch({SIGABRT, SIGTERM}, [](int sig){});

    // add crash handler
    libcpp::crash_handler::instance()->prevent_set_unhandled_exception_filter();
    libcpp::crash_handler::instance()->set_local_path(config.crash_path);
    LOG_DEBUG("livermore-broker crash set local path={}", config.crash_path);

    return error::ok;
}

err_t application_base::run()
{
    while (true) { LOG_DEBUG("service running..."); libcpp::application::msleep(500); }
    return error::ok;
}

err_t application_base::stop()
{
    LOG_DEBUG("service stopped.");
    return error::ok;
}

}