#ifndef MANAGE_H
#define MANAGE_H

#include <iostream>
#include <libcpp/os/dll.h>
#include <libcpp/os/application.hpp>

C_STYLE_EXPORT void manage_info();

C_STYLE_EXPORT void manage_init();

C_STYLE_EXPORT int manage_run();

C_STYLE_EXPORT void manage_exit();

#endif