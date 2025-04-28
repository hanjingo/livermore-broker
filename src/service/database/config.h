#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#include "error.h"
#include "config_base.h"

namespace database
{

struct config : public common::config_base
{
    config() : common::config_base() {};
    ~config() {};

    void clear() override;
    err_t load(const char* filepath) override;
    err_t check() override;
};

}

#endif