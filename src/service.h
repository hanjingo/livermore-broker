#ifndef SERVICE_H
#define SERVICE_H

#include <libcpp/log/log.hpp>
#include <libcpp/os/application.hpp>
#include <libcpp/os/process.hpp>
#include <libcpp/os/dll.h>
#include <libcpp/io/filepath.hpp>
#include <libcpp/sync/coroutine.hpp>
#include <libcpp/testing/error.hpp>

namespace livermore
{
using error_t = libcpp::error_v2<int>;

static error_t ok(0, nullptr);
static error_t dll_open_fail(1, nullptr);
static error_t fn_info_not_found(2, nullptr);
static error_t fn_init_not_found(3, nullptr);
static error_t fn_run_not_found(4, nullptr);
static error_t fn_exit_not_found(5, nullptr);

class service
{
public:
    typedef void (* fn_info)(void);
    typedef void (* fn_init)(void);
    typedef int (* fn_run)(void);
    typedef void (* fn_exit)(void);

public:
    service() {}
    ~service() {}

    livermore::error_t start(const char* file, bool async = false);

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