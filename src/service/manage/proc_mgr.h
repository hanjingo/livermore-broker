#ifndef PROC_MGR_H
#define PROC_MGR_H

#include <iostream>
#include <mutex>
#include <unordered_map>

#include <libcpp/log/logger.hpp>
#include <libcpp/os/application.hpp>
#include <libcpp/os/process.hpp>
#include <libcpp/types/singleton.hpp>
#include <libcpp/sync/defer.hpp>

#include "version.h"
#include "error.h"
#include "proc.h"
#include "config_mgr.h"

namespace manage
{

class proc_mgr
{
public:
    proc_mgr() = delete;
    proc_mgr(const proc_mgr&) = delete;
    proc_mgr& operator=(const proc_mgr&) = delete;

    static error watch();
    static error add_watch_list(const pid_t pid);

    static std::mutex mu;
    static std::unordered_map<pid_t, proc&&> m_proc;
};

}

#endif