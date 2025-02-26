#include "proc_mgr.h"

namespace manage
{

error proc_mgr::watch()
{
    while (true)
    {
        for (auto ptr = m_proc.begin(); ptr != m_proc.end(); ++ptr)
        {
            if (ptr->second.is_running())
                continue;

            // TODO restart p
        }

        std::this_thread::sleep_for(config_mgr::serv_scan_dur);
    }
}

error proc_mgr::add_watch_list(const pid_t pid)
{
    mu.lock();
    DEFER(mu.unlock());
    
    auto itr = m_proc.find(pid);
    if (itr != m_proc.end())
        return error::can_not_add_watch_list_twice;

    proc p{pid};
    m_proc.emplace(pid, std::move(p));
    return error::ok;
}

}