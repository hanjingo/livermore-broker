#ifndef UTIL_H
#define UTIL_H

#include <libcpp/encoding/json.hpp>
#include "market_data.h"
#include "market_data_util.h"

namespace broadcast
{

void md_to_json(market_data* md, libcpp::json& js);

}

#endif