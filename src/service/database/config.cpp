#include "config.h"

namespace database
{

void config::clear()
{
    config_base::clear();
    
}

err_t config::load(const char* filepath)
{
    clear();

    LOG_INFO("load file {}", filepath);
    // parse config
    auto err = config_base::load(filepath);
    if (err != error::ok)
        return err;
    
    return check();
}

err_t config::check()
{
    auto err = config_base::check();
    if (err != error::ok)
        return err;

    return error::ok;
}

}