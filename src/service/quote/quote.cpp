#include "quote.h"

void info()
{
    // TODO
}

int init()
{
    return static_cast<int>(quote::application::instance().init());
}

int run()
{
    return static_cast<int>(quote::application::instance().run());
}

int stop()
{
    return static_cast<int>(quote::application::instance().stop());
}