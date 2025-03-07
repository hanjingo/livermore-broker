#ifndef ERROR_BASE_H
#define ERROR_BASE_H

#ifndef ERROR_MASK
#define ERROR_MASK 0x3FF
#endif

#include <string>
#include <libcpp/encoding/hex.hpp>

using err_t = int;

#define __err_cat(a, b) a##b
#define _err_cat(a, b) __err_cat(a, b)
#define ERR_DESC(name, desc) static const char* _err_cat(err_, name) = desc;
#define ERR_WHAT(name) _err_cat(err_, name)

namespace common
{

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

common_error_end,
};

// static const char* err_what(const err_t err)
// {
// switch (err)
// {
//     case ok: return "ok";
//     case fail: return "fail";
//     case dll_open_fail: return "dll open fail";
//     case fn_info_not_found: return "fn_info_not_found";
//     case fn_init_not_found: return "fn_init_not_found";
//     case fn_run_not_found: return "fn_run_not_found";
//     case fn_stop_not_found: return "fn_stop_not_found";
//     case read_config_fail: return "read_config_fail";
//     case log_file_size_too_small: return "log_file_size_too_small";
//     case log_file_size_too_big: return "log_file_size_too_big";
//     case log_file_num_too_small: return "log_file_num_too_small";
//     case log_file_num_too_big: return "log_file_num_too_big";
//     case log_lvl_too_small: return "log_lvl_too_small";
//     case log_lvl_too_big: return "log_lvl_too_big";
//     case crash_path_permission_denied: return "crash_path_permission_denied";
    
//     case common_error_end: return "common_error_end";
// }
// }

ERR_DESC(ok, "no problem")
ERR_DESC(fail, "fail")
ERR_DESC(dll_open_fail, "dll_open_fail")
ERR_DESC(fn_init_not_found, "fn_init_not_found")
ERR_DESC(fn_run_not_found, "fn_run_not_found")
ERR_DESC(fn_stop_not_found, "fn_stop_not_found")
ERR_DESC(read_config_fail, "read_config_fail")
ERR_DESC(log_file_size_too_small, "log_file_size_too_small")
ERR_DESC(log_file_size_too_big, "log_file_size_too_big")
ERR_DESC(log_file_num_too_small, "log_file_num_too_small")
ERR_DESC(log_file_num_too_big, "log_file_num_too_big")
ERR_DESC(log_lvl_too_small, "log_lvl_too_small")
ERR_DESC(log_lvl_too_big, "log_lvl_too_big")
ERR_DESC(crash_path_permission_denied, "crash_path_permission_denied")
ERR_DESC(common_error_end, "common_error_end")


static error real_error_code(const err_t err) { return error(ERROR_MASK & err); }
static int err_to_int(const error err) { return static_cast<int>(err); }
static std::string err_to_hex(const int err, bool upper_case = true) 
{ 
    return std::string("0x").append(libcpp::hex::to_str(err)); 
};

}

#endif