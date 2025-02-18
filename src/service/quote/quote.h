#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>
#include <libcpp/util/dll.h>

namespace livermore
{

class quote
{
public:
    DLL_EXPORT static void version();

    DLL_EXPORT void run();
};

}

#endif