#ifndef APPLICATION_H
#define APPLICATION_H

#include "version.h"
#include "error.h"
#include "config.h"
#include "application_base.h"

#include "ctp.h"
#include "xtp.h"
#include "tx.h"

#define XTP_NUM

namespace quote
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

    quote::config       conf;
    quote::ctp*         ctp_obj;
    quote::xtp*         xtp_obj;
    quote::tx*          tx_obj;
};

}

#endif