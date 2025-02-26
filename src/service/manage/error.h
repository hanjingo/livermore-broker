#ifndef ERROR_H
#define ERROR_H

namespace manage
{

// [0, 1023]
enum class error
{
// common error code [0, 63]
ok = 0x0,

// error code [64, 127]
config_err_start = 0x40,
read_config_fail,
log_file_size_too_small,
log_file_size_too_big,
log_file_num_too_small,
log_file_num_too_big,
log_lvl_too_small,
log_lvl_too_big,
crash_path_permission_denied,
serv_scan_too_busy,
serv_scan_too_slow,
serv_proc_too_much,
config_err_end = 0x7F,

// error code [128, 255]
proc_err_start = 0x80,
can_not_add_watch_list_twice,
proc_err_end = 0xFF,

};

}

#endif