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
#include <libcpp/util/string_util.hpp>

#include "version.h"
#include "error.h"
#include "config_mgr.h"

namespace manage
{

using pid_t = libcpp::process::pid_t;

class proc
{
public:
    proc(const std::string& tag) : _tag{tag} 
    {
#if defined(WIN32)
        _cmd = "livermore-broker.exe";
#else
        _cmd = "./livermore-broker";
#endif
    }
    ~proc() {}
    
    pid_t pid();
    std::string& tag();
    err_t run(const bool single = true);
    bool is_running();
    
private:
    std::string _tag;
    std::string _cmd;
    libcpp::process::child_t _child;
};

class proc_mgr
{
public:
    proc_mgr() {}
    ~proc_mgr() {}
    proc_mgr(const proc_mgr&) = delete;
    proc_mgr& operator=(const proc_mgr&) = delete;

    static proc_mgr& instance();

    error watch();
    error add_watch_list(proc&& p);

private:
    std::mutex _mu;
    std::unordered_map<pid_t, proc&&> _m_proc;
};

}

#endif