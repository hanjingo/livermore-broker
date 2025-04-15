#ifndef CONFIG_BASE_H
#define CONFIG_BASE_H

#include <string>
#include <libcpp/encoding/ini.hpp>
#include <libcpp/log/logger.hpp>

#include "error_base.h"

namespace common
{

struct config_base
{
    config_base() {};
    ~config_base() {};

    template<typename T>
    static T get_value(const char* filepath, const char* section, const char* key)
    {
        libcpp::ini file;
        if (!file.read_file(filepath))
            return "";
        
        auto sub_cfg = file.get_child(section);
        return sub_cfg.get<T>(key);
    }

    virtual void clear();
    virtual err_t load(const char* filepath);
    virtual err_t check();
    virtual std::string to_str();

    libcpp::ini cfg;
    std::string name;
    std::string module;

    std::string log_path;
    unsigned long long log_size;
    int log_file_num;
    bool log_rotate_on_open;
    libcpp::log_lvl log_min_lvl;

    std::string crash_path;
};

}

#endif