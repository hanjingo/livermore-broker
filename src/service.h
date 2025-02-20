#ifndef SERVICE_H
#define SERVICE_H

#include <libcpp/log/log.hpp>
#include <libcpp/os/application.hpp>
#include <libcpp/os/process.hpp>
#include <libcpp/util/dll.h>
#include <libcpp/io/filepath.hpp>
#include <libcpp/sync/coroutine.hpp>

namespace livermore
{

class service
{
public:
    typedef void (* fn_info)(void);
    typedef void (* fn_init)(void);
    typedef int (* fn_run)(void);
    typedef void (* fn_exit)(void);

    enum error {
        ok = 0,
        error_dll_open_fail,
        error_fn_info_not_found,
        error_fn_init_not_found,
        error_fn_run_not_found,
        error_fn_exit_not_found,
    };

public:
    service() {}
    ~service() {}

    livermore::service::error start(const char* file, bool async = false);

    void stop();

private:
    void* _handler;
    fn_info _finfo = nullptr;
    fn_init _finit = nullptr;
    fn_run  _frun  = nullptr;
    fn_exit _fexit = nullptr;
};

}

#endif