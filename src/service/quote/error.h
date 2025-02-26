#ifndef ERROR_H
#define ERROR_H

namespace quote
{

// [1024, 2048]
enum class error
{
// common error code [0, 63]
ok = 0x0,

// error code [1024, 2047]
config_err_start = 0x400,
read_config_fail,
log_file_size_too_small,
log_file_size_too_big,
log_file_num_too_small,
log_file_num_too_big,
log_lvl_too_small,
log_lvl_too_big,
crash_path_permission_denied,
config_err_end = 0x7FF,

// error code [2048, 4095]

// error code [4096, 8191]

};

}

#endif