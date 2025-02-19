#include "quote.h"

void info()
{
    std::cout << "quote info" << std::endl;
}

void init()
{
    std::cout << "quote init" << std::endl;
}

void run()
{
    std::cout << "quote run" << std::endl;

    while (true) { libcpp::application::msleep(5000); }
}

void exit()
{
    std::cout << "quote exit" << std::endl;
}