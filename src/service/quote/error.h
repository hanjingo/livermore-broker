#ifndef ERROR_H
#define ERROR_H

#include "error_base.h"

namespace quote
{

// [1024, 4095]
enum error : err_t
{

ok = common::ok,

quote_err_start = 0x400,
ctp_unknow_error,
ctp_addr_empty,
ctp_addr_invalid,
ctp_flow_md_path_empty,
ctp_create_flow_md_path_fail,
ctp_null,
ctp_current_status_not_allowed_connect,
ctp_current_status_not_allowed_login,
ctp_current_status_not_allowed_logging_out,
ctp_request_user_login_fail,
ctp_request_user_login_timeout,
ctp_create_mdapi_fail,
ctp_connect_timeout,
ctp_disconnected,
ctp_too_much_unhandled_request,
ctp_too_much_request,

xtp_unknow_error, // 0x411
xtp_null,
xtp_current_stat_not_allowd_init,
xtp_addr_empty,
xtp_addr_invalid,
xtp_connect_serv_fail,
xtp_connect_already_exist,
xtp_input_error,
xtp_current_status_not_allowed_login,
xtp_login_fail,
xtp_current_status_not_allowed_logging_out,
xtp_logout_fail,
xtp_subscribe_fail,
xtp_unsubscribe_fail,

ctp_read_fail = 0x1001,
ctp_write_fail,

ctp_heartbeat_timeout = 0x2001,
ctp_heartbeat_fail,
ctp_recv_invalid_msg,
error_end = 0x1FFF,
};

template<typename T>
static std::string err_what(const T err)
{

std::string ret = common::err_what(err);
if (!ret.empty())
    return ret;

switch (err)
{
    case quote_err_start: return "quote_err_start";

    case ctp_unknow_error: return "ctp_unknow_error";
    case ctp_addr_empty: return "ctp_addr_empty";
    case ctp_addr_invalid: return "ctp_addr_invalid";
    case ctp_flow_md_path_empty: return "ctp_flow_md_path_empty";
    case ctp_create_flow_md_path_fail: return "ctp_create_flow_md_path_fail";
    case ctp_null: return "ctp_null";
    case ctp_current_status_not_allowed_connect: return "ctp_current_status_not_allowed_connect";
    case ctp_current_status_not_allowed_login: return "ctp_current_status_not_allowed_login";
    case ctp_current_status_not_allowed_logging_out: return "ctp_current_status_not_allowed_logging_out";
    case ctp_request_user_login_fail: return "ctp_request_user_login_fail";
    case ctp_request_user_login_timeout: return "ctp_request_user_login_timeout";
    case ctp_create_mdapi_fail: return "ctp_create_mdapi_fail";
    case ctp_connect_timeout: return "ctp_connect_timeout";
    case ctp_disconnected: return "ctp_disconnected";
    case ctp_too_much_unhandled_request: return "ctp_too_much_unhandled_request";
    case ctp_too_much_request: return "ctp_too_much_request";

    case xtp_unknow_error: return "xtp_unknow_error";
    case xtp_null: return "xtp_null";
    case xtp_current_stat_not_allowd_init: return "xtp_current_stat_not_allowd_init";
    case xtp_addr_empty: return "xtp_addr_empty";
    case xtp_addr_invalid: return "xtp_addr_invalid";
    case xtp_connect_serv_fail: return "xtp_connect_serv_fail";
    case xtp_connect_already_exist: return "xtp_connect_already_exist";
    case xtp_input_error: return "xtp_input_error";
    case xtp_current_status_not_allowed_login: return "xtp_current_status_not_allowed_login";
    case xtp_login_fail: return "xtp_login_fail";
    case xtp_current_status_not_allowed_logging_out: return "xtp_current_status_not_allowed_logging_out";
    case xtp_logout_fail: return "xtp_logout_fail";
    case xtp_subscribe_fail: return "xtp_subscribe_fail";
    case xtp_unsubscribe_fail: return "xtp_unsubscribe_fail";

    case ctp_read_fail: return "ctp_read_fail";
    case ctp_write_fail: return "ctp_write_fail";

    case ctp_heartbeat_timeout: return "ctp_heartbeat_timeout";
    case ctp_heartbeat_fail: return "ctp_heartbeat_fail";
    case ctp_recv_invalid_msg: return "ctp_recv_invalid_msg";
    case error_end: return "error_end";
}
}

}
#endif