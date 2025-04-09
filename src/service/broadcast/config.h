#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>
#include <unordered_map>

#include "error.h"
#include "version.h"
#include "config_base.h"

namespace broadcast
{

struct config : public common::config_base
{
    config() : common::config_base() {};
    ~config() {};

    void clear() override;
    err_t load(const char* filepath) override;
    err_t check() override;

    std::vector<std::uint16_t> tcp_ports;
    std::vector<std::uint16_t> cpu_cores;
};

}

#endif