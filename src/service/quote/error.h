#ifndef ERROR_H
#define ERROR_H

#include "error_base.h"

namespace quote
{

// [1024, 4095]
enum error : err_t
{

ok = 0x0,

error_start = 0x400,
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

xtp_null,

ctp_read_fail = 0x1001,
ctp_write_fail,

ctp_heartbeat_timeout = 0x2001,
ctp_heartbeat_fail,
ctp_recv_invalid_msg,
error_end = 0x1FFF,
};

}
#endif