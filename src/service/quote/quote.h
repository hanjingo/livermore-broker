#ifndef QUOTE_H
#define QUOTE_H

#include <libcpp/util/dll.h>

#include "application.h"
#include "version.h"

C_STYLE_EXPORT void info();

C_STYLE_EXPORT int init();

C_STYLE_EXPORT int run();

C_STYLE_EXPORT int stop();

#endif