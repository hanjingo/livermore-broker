#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>
#include <libcpp/util/dll.h>
#include <libcpp/os/application.hpp>

C_STYLE_EXPORT void quote_info();

C_STYLE_EXPORT void quote_init();

C_STYLE_EXPORT int quote_run();

C_STYLE_EXPORT void quote_exit();

#endif