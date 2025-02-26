#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>

#include <libcpp/log/logger.hpp>
#include <libcpp/encoding/ini.hpp>
#include <libcpp/testing/crash.hpp>
#include <libcpp/testing/exception.hpp>
#include <libcpp/os/signal.hpp>
#include <libcpp/os/env.h>
#include <libcpp/io/file.hpp>

#include "version.h"
#include "error.h"
#include "config_mgr.h"

namespace quote
{

class application
{
public:
    application() = delete;
    application(const application&) = delete;
    application& operator=(const application&) = delete;
    
    static error init();
    static error run();
    static error stop();
};

}

#endif