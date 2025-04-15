#ifndef ERROR_H
#define ERROR_H

#define ERROR_MASK 0x800

#include "error_base.h"

namespace database
{

enum error : err_t
{
ok = common::ok,
err_start = common::common_error_end,



};

}

#endif