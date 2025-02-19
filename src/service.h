#ifndef SERVICE_H
#define SERVICE_H

#include <libcpp/os/application.hpp>
#include <libcpp/os/process.hpp>
#include <libcpp/util/dll.hpp>

namespace livermore
{

class service
{
public:
    service() {}
    ~service() {}

    template <typename... Args>
    void start(Args&&... args);

    template <typename... Args>
    void stop(Args&&... args);

private:
    void (* _ptr_info)(void) = nullptr;
    void (* _ptr_init)(void) = nullptr;
    void (* _ptr_run)(void) = nullptr;
    void (* _ptr_exit)(void) = nullptr;
};

}

#endif