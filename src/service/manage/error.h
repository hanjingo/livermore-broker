#ifndef ERROR_H
#define ERROR_H

#include "error_base.h"

namespace manage
{

// [0x1000, 0x3FFF]
enum error : err_t
{
ok = 0x0,

manage_error_start = 0x1000,
serv_scan_too_busy,
serv_scan_too_slow,
serv_proc_too_much,

can_not_add_watch_list_twice = 0x2000,
proc_run_fail,
proc_already_running,
proc_file_path_empty,
proc_file_not_exist,

manage_error_end = 0x3FFF,
};

}

#endif