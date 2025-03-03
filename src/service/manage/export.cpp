#include "export.h"
#include "application.h"

void info()
{
    // TODO
}

int init()
{
    return static_cast<int>(manage::application::instance().init());
}

int run()
{
    return static_cast<int>(manage::application::instance().run());
}

int stop()
{
    return static_cast<int>(manage::application::instance().stop());
}