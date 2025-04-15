#ifndef ERROR_BASE_H
#define ERROR_BASE_H

#ifndef ERROR_MASK
#define ERROR_MASK 0x0
#endif

#include <string>
#include <libcpp/encoding/hex.hpp>
#include <libcpp/testing/error.hpp>

using err_t = int;

namespace common
{

enum error : err_t
{
ok = ERROR_MASK & 0x0,
fail, 
dll_open_fail,
fn_info_not_found,
fn_init_not_found,
fn_run_not_found,
fn_stop_not_found,
read_config_fail,
conf_name_invalid,
conf_module_invalid,
conf_module_not_match,
log_file_size_too_small,
log_file_size_too_big,
log_file_num_too_small,
log_file_num_too_big,
log_lvl_too_small,
log_lvl_too_big,
crash_path_permission_denied,

common_error_end,
};

template<typename T>
static std::string err_what(const T err)
{
switch (err)
{
    case ok: return "ok";
    case fail: return "fail";
    case dll_open_fail: return "dll open fail";
    case fn_info_not_found: return "fn_info_not_found";
    case fn_init_not_found: return "fn_init_not_found";
    case fn_run_not_found: return "fn_run_not_found";
    case fn_stop_not_found: return "fn_stop_not_found";
    case read_config_fail: return "read_config_fail";
    case log_file_size_too_small: return "log_file_size_too_small";
    case log_file_size_too_big: return "log_file_size_too_big";
    case log_file_num_too_small: return "log_file_num_too_small";
    case log_file_num_too_big: return "log_file_num_too_big";
    case log_lvl_too_small: return "log_lvl_too_small";
    case log_lvl_too_big: return "log_lvl_too_big";
    case crash_path_permission_denied: return "crash_path_permission_denied";
    
    case common_error_end: return "common_error_end";
    default: return "";
}
}

template <typename T>
static error real_error_code(const T err) { return error(ERROR_MASK & err); }

template <typename T>
static int err_to_int(const T err) { return static_cast<int>(err); }

template <typename T>
static std::string err_to_hex(const T err, bool upper_case = true) 
{ 
    return std::string("0x").append(libcpp::hex::to_str(err, upper_case)); 
};

}

#endif