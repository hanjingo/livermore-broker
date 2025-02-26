#include "service.h"

namespace livermore
{

error service::load(const char* file)
{
    _handler = dll_open(file, DLL_RTLD_NOW);
    if (_handler == nullptr)
        return error::dll_open_fail;

    _finfo = (fn_info)dll_get(_handler, "info");
    if (_finfo == nullptr)
        return error::fn_info_not_found;

    _finit = (fn_init)dll_get(_handler, "init");
    if (_finit == nullptr)
        return error::fn_init_not_found;

    _frun  = (fn_run)dll_get(_handler, "run");
    if (_frun == nullptr)
        return error::fn_run_not_found;

    _fstop = (fn_stop)dll_get(_handler, "stop");
    if (_fstop == nullptr)
        return error::fn_stop_not_found;

    return error::ok;
}

error service::init()
{
    return static_cast<error>(_finit());
}

error service::start(bool async)
{
    if (async)
    {
        std::thread([&](){ _frun(); }).detach();
        return error::ok;
    }

    return static_cast<error>(_frun());
}

error service::stop()
{
    if (_handler == nullptr)
        return error::fn_stop_not_found;

    if (_fstop != nullptr)
        return static_cast<error>(_fstop());

    dll_close(_handler);
    _handler = nullptr;
    _finfo   = nullptr;
    _finit   = nullptr;
    _frun    = nullptr;
    _fstop   = nullptr;
    return error::ok;
}

}