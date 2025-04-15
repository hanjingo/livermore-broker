#include "proc_mgr.h"

#include <libcpp/log/logger.hpp>
#include <libcpp/os/application.hpp>
#include <libcpp/types/singleton.hpp>
#include <libcpp/sync/defer.hpp>
#include <libcpp/util/string_util.hpp>

namespace manage
{

pid_t proc::pid()
{
    return (_child.valid() ? _child.id() : 0);
}

std::string& proc::tag()
{
    return _tag;
}

err_t proc::run(const bool single)
{
    // check single
    if (single && is_running())
        return error::proc_already_running;

    auto cmd = libcpp::string_util::fmt("{} --name={}", _cmd, _tag);
    _child = libcpp::process::child(cmd);
    _child.detach();
    return error::ok;
}

bool proc::is_running()
{
    return _child.valid() && _child.running();
}

error proc_mgr::watch(const std::chrono::milliseconds dur)
{
    while (true)
    {
        for (auto ptr = _m_proc.begin(); ptr != _m_proc.end(); ++ptr)
        {
            if (ptr->second.is_running())
                continue;

            ptr->second.run(true);
            LOG_INFO("server {} run...", ptr->second.tag());
        }

        std::this_thread::sleep_for(dur);
    }
}

error proc_mgr::add_watch_list(proc&& p)
{
    _mu.lock();
    DEFER(_mu.unlock());

    auto itr = _m_proc.find(p.pid());
    if (itr != _m_proc.end())
        return error::can_not_add_watch_list_twice;

    _m_proc.emplace(p.pid(), std::move(p));
    LOG_INFO("add watch list with proc tag={}", p.tag());
    return error::ok;
}

}