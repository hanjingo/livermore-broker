#include "proc_mgr.h"

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

    auto cmd = libcpp::string_util::fmt("{} --module={}", _cmd, _tag);
    LOG_DEBUG("cmd={}", cmd);
    _child = libcpp::process::child(cmd);
    _child.detach();
    return error::ok;
}

bool proc::is_running()
{
    return _child.valid() && _child.running();
}


proc_mgr& proc_mgr::instance()
{
    static proc_mgr inst;
    return inst;
}

error proc_mgr::watch()
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

        std::this_thread::sleep_for(config_mgr::instance().serv_scan_dur);
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