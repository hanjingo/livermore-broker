#include "quote.h"

void info()
{
    // TODO
}

int init()
{
    return static_cast<int>(quote::application::init());
}

int run()
{
    return static_cast<int>(quote::application::run());
}

int stop()
{
    return static_cast<int>(quote::application::stop());
}