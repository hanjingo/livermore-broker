#ifndef APPLICATION_H
#define APPLICATION_H

#define L2

#include "version.h"
#include "error.h"
#include "config.h"
#include "application_base.h"
#include "cleaner.h"

namespace database
{

class application : public common::application_base
{
public:
    application() : common::application_base() { };
    ~application() {};
    application(const application&) = delete;
    application& operator=(const application&) = delete;

    static application& instance();

    err_t init(const char* id);
    err_t run() override;
    err_t stop() override;

    database::config conf;
};

}

#endif