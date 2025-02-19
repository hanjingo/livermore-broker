#include "quote.h"

namespace livermore
{

void quote::version()
{
    std::cout << "quote version" << std::endl;
}

void quote::run()
{
    std::cout << "quote run" << std::endl;

    while (true) { libcpp::application::msleep(5000); }
}

}