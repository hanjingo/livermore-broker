#include <thread>
#include <libcpp/os/dll.h>
#include <libcpp/sync/coroutine.hpp>

#include "service.h"

namespace livermore
{

err_t service::load(const char* file)
{
    _handler = dll_open(file, DLL_RTLD_NOW);
    if (_handler == nullptr)
        return common::error::dll_open_fail;

    _finfo = (fn_info)dll_get(_handler, "info");
    if (_finfo == nullptr)
        return common::error::fn_info_not_found;

    _finit = (fn_init)dll_get(_handler, "init");
    if (_finit == nullptr)
        return common::error::fn_init_not_found;

    _frun  = (fn_run)dll_get(_handler, "run");
    if (_frun == nullptr)
        return common::error::fn_run_not_found;

    _fstop = (fn_stop)dll_get(_handler, "stop");
    if (_fstop == nullptr)
        return common::error::fn_stop_not_found;

    return common::error::ok;
}

err_t service::init()
{
    return static_cast<common::error>(_finit());
}

err_t service::start(bool async)
{
    if (async)
    {
        std::thread([&](){ _frun(); }).detach();
        return common::error::ok;
    }

    return static_cast<common::error>(_frun());
}

err_t service::stop()
{
    if (_handler == nullptr)
        return common::error::fn_stop_not_found;

    if (_fstop != nullptr)
        return static_cast<common::error>(_fstop());

    dll_close(_handler);
    _handler = nullptr;
    _finfo   = nullptr;
    _finit   = nullptr;
    _frun    = nullptr;
    _fstop   = nullptr;
    return common::error::ok;
}

}