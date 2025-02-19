#ifndef SERVICE_H
#define SERVICE_H

#include <libcpp/os/application.hpp>
#include <libcpp/os/process.hpp>

#include <quote.h>

namespace livermore
{

class service
{
public:
    service() {}
    ~service() {}

    static void start(const char* name) {}
};

}

#endif