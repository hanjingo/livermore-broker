#ifndef PROC_H
#define PROC_H

#include <mutex>
#include <libcpp/os/process.hpp>

namespace manage
{

using pid_t = libcpp::process::pid_t;

class proc
{
public:
    proc(const pid_t pid) {}
    ~proc() {}

    bool is_running();
};

}

#endif