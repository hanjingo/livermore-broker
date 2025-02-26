#ifndef SERVICE_H
#define SERVICE_H

#include <thread>
#include <libcpp/os/dll.h>
#include <libcpp/sync/coroutine.hpp>

namespace livermore
{
enum class error
{
    // error code range [0, 99]
    ok = 0,
    fail,
    dll_open_fail,
    fn_info_not_found,
    fn_init_not_found,
    fn_run_not_found,
    fn_stop_not_found,

    // give [100, ...] to service
};

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

    livermore::error load(const char* file);
    livermore::error init();
    livermore::error start(bool async = false);
    livermore::error stop();

private:
    void* _handler;
    fn_info _finfo = nullptr;
    fn_init _finit = nullptr;
    fn_run  _frun  = nullptr;
    fn_stop _fstop = nullptr;
};

}

#endif