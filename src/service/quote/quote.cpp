#include "quote.h"

void quote_info()
{
    std::cout << "quote info" << std::endl;
}

void quote_init()
{
    std::cout << "quote init" << std::endl;
}

int quote_run()
{
    std::cout << "quote run" << std::endl;

    while (true) { libcpp::application::msleep(5000); }
    return 0;
}

void quote_exit()
{
    std::cout << "quote exit" << std::endl;
}