#ifndef APPLICATION_H
#define APPLICATION_H

#include "version.h"
#include "error.h"
#include "application_base.h"
#include "config.h"
#include "proc_mgr.h"

namespace manage
{

class application : public common::application_base
{
public:
    application() : common::application_base() { };
    ~application() {};
    application(const application&) = delete;
    application& operator=(const application&) = delete;

    static application& instance();

    err_t init();
    err_t run() override;

    manage::config conf;
    manage::proc_mgr procs;
};

}

#endif