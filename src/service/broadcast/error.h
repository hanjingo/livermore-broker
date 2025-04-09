#ifndef ERROR_H
#define ERROR_H

#define ERROR_MASK 0x400

#include "error_base.h"

namespace broadcast
{

enum error : err_t
{
ok = 0x0,
err_start = common::common_error_end,

bind_cpu_core_fail,
tcp_gate_create_fail,
};

}

#endif