#include "manage.h"

void info()
{
    // TODO
}

int init()
{
    return static_cast<int>(manage::application::init());
}

int run()
{
    return static_cast<int>(manage::application::run());
}

int stop()
{
    return static_cast<int>(manage::application::stop());
}