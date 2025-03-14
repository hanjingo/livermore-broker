#ifndef ERROR_H
#define ERROR_H

#define ERROR_MASK 0x100

#include "error_base.h"

namespace manage
{

enum error : err_t
{
ok = common::ok,
err_start = common::common_error_end,

serv_scan_too_busy,
serv_scan_too_slow,
serv_proc_too_much,

can_not_add_watch_list_twice,
proc_run_fail,
proc_already_running,
proc_file_path_empty,
proc_file_not_exist,
};

template<typename T>
static std::string err_what(const T err)
{

std::string ret = common::err_what(err);
if (!ret.empty())
    return ret;

switch (err)
{
    case serv_scan_too_busy: return "serv_scan_too_busy";
    case serv_scan_too_slow: return "serv_scan_too_slow";
    case serv_proc_too_much: return "serv_proc_too_much";

    case can_not_add_watch_list_twice: return "can_not_add_watch_list_twice";
    case proc_run_fail: return "proc_run_fail";
    case proc_already_running: return "proc_already_running";
    case proc_file_path_empty: return "proc_file_path_empty";
    case proc_file_not_exist: return "proc_file_not_exist";

    default: return "";
}
}

}

#endif