#include "export.h"
#include "error.h"
#include "application.h"

void info()
{
    // TODO
}

int init()
{
    return static_cast<int>((~ERROR_MASK) & quote::application::instance().init());
}

int run()
{
    return static_cast<int>((~ERROR_MASK) & quote::application::instance().run());
}

int stop()
{
    return static_cast<int>((~ERROR_MASK) & quote::application::instance().stop());
}