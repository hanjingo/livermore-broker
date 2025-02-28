#ifndef APPLICATION_H
#define APPLICATION_H

#include "version.h"
#include "error.h"
#include "application_base.h"

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
};

}

#endif