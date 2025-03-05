#ifndef SERVICE_H
#define SERVICE_H

#include "common/error_base.h"

namespace livermore
{

class service
{
public:
    typedef void (* fn_info)(void);
    typedef int (* fn_init)(void);
    typedef int (* fn_run)(void);
    typedef int (* fn_stop)(void);

public:
    service() {}
    ~service() {}

    err_t load(const char* file);
    err_t init();
    err_t start(bool async = false);
    err_t stop();

private:
    void* _handler;
    fn_info _finfo = nullptr;
    fn_init _finit = nullptr;
    fn_run  _frun  = nullptr;
    fn_stop _fstop = nullptr;
};

}

#endif