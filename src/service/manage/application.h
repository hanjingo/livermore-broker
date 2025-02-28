#ifndef APPLICATION_H
#define APPLICATION_H

#include "version.h"
#include "error.h"
#include "application_base.h"
#include "config_mgr.h"
#include "proc_mgr.h"

namespace manage
{

class application : public common::application_base
{
public:
    application() {};
    ~application() {};
    application(const application&) = delete;
    application& operator=(const application&) = delete;

    static application& instance();

    err_t init();
    err_t run();
    err_t stop();
};

}

#endif