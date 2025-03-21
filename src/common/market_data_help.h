#include "market_data.h"

#include <string>

namespace common
{

void md_reset(market_data* md);

std::string md_fmt(const market_data* md);

bool md_equal(const market_data* md1, const market_data* md2, std::string& memo);

void md_copy(market_data* dst, market_data* src);

}