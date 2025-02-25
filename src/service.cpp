#include "service.h"

namespace livermore
{

livermore::error_t service::start(const char* file, bool async)
{
    _handler = dll_open(file, DLL_RTLD_NOW);
    if (_handler == nullptr)
        return dll_open_fail;

    _finfo = (fn_info)dll_get(_handler, "quote_info");
    if (_finfo == nullptr)
        return fn_info_not_found;

    _finit = (fn_init)dll_get(_handler, "quote_init");
    if (_finit == nullptr)
        return fn_init_not_found;

    _frun  = (fn_run)dll_get(_handler, "quote_run");
    if (_frun == nullptr)
        return fn_run_not_found;

    _fexit = (fn_exit)dll_get(_handler, "quote_exit");
    if (_fexit == nullptr)
        return fn_exit_not_found;

    if (async)
    {
        std::thread([&](){ _frun(); }).detach();
        return ok;
    }

    return error_t(_frun());
}

void service::stop()
{
    if (_handler == nullptr)
        return;

    if (_fexit != nullptr)
        _fexit();

    dll_close(_handler);
    _handler = nullptr;
    _finfo   = nullptr;
    _finit   = nullptr;
    _frun    = nullptr;
    _fexit   = nullptr;
}

}