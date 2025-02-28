#ifndef APPLICATION_BASE_H
#define APPLICATION_BASE_H

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

#include "error_base.h"
#include "config_mgr_base.h"

namespace common
{

class application_base
{
public:
    application_base() {};
    ~application_base() {};
    application_base(const application_base&) = delete;
    application_base& operator=(const application_base&) = delete;

    static application_base& instance();

    virtual err_t init();
    virtual err_t run();
    virtual err_t stop();
};

}

#endif