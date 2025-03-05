#ifndef APPLICATION_BASE_H
#define APPLICATION_BASE_H

#include "error_base.h"
#include "config_base.h"

namespace common
{

class application_base
{
public:
    application_base() {};
    ~application_base() {};

    virtual err_t init(const common::config_base& config);
    virtual err_t run();
    virtual err_t stop();
};

}

#endif