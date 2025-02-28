#ifndef SENTINEL_H
#define SENTINEL_H

#include <thread>
#include <chrono>
#include <libcpp/os/dll.h>

#include "version.h"

C_STYLE_EXPORT void info();

C_STYLE_EXPORT int init();

C_STYLE_EXPORT int run();

C_STYLE_EXPORT int stop();

#endif