#ifndef ERROR_BASE_H
#define ERROR_BASE_H

#ifndef ERROR_MASK
#define ERROR_MASK 0x3FF
#endif

using err_t = int;

namespace common
{

static int real_error_code(const err_t err) { return ERROR_MASK & err; }

enum error : err_t
{
ok = 0x0,
fail, 
dll_open_fail,
fn_info_not_found,
fn_init_not_found,
fn_run_not_found,
fn_stop_not_found,
read_config_fail,
log_file_size_too_small,
log_file_size_too_big,
log_file_num_too_small,
log_file_num_too_big,
log_lvl_too_small,
log_lvl_too_big,
crash_path_permission_denied,

common_error_end = 0x3FF,
};

}

#endif