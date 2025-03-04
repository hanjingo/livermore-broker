#ifndef ERROR_H
#define ERROR_H

#include "error_base.h"

namespace quote
{

// [1024, 4095]
enum error : err_t
{

ok = 0x0,

error_start = 0x100,
flow_md_path_empty,
create_flow_md_path_fail,
error_end = 0xFFF,
};

}

#endif