#include "manage.h"

void manage_info()
{
    std::cout << "manage info" << std::endl;
}

void manage_init()
{
    std::cout << "manage init" << std::endl;
}

int manage_run()
{
    std::cout << "manage run" << std::endl;

    while (true) { libcpp::application::msleep(5000); }

    std::cout << "manage quit" << std::endl;
    return 0;
}

void manage_exit()
{
    std::cout << "manage exit" << std::endl;
}