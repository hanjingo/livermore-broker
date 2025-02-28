#ifndef ERROR_BASE_H
#define ERROR_BASE_H

using err_t = int;

namespace common
{

// [0, 0x3FF]
enum error : err_t
{
ok = 0x0,
fail, 
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