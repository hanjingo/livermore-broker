#ifndef APPLICATION_H
#define APPLICATION_H

#include "version.h"
#include "error.h"
#include "application_base.h"
#include "config_mgr.h"
#include "ctp.h"

#include <libcpp/io/filepath.hpp>

namespace quote
{

class application : public common::application_base
{
public:
    application() {};
    ~application() {};
    application(const application&) = delete;
    application& operator=(const application&) = delete;

    static application& instance();

    err_t init() override;
    err_t run() override;

private:
    ctp _ctp;
};

}

#endif