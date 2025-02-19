#include "service.h"

namespace livermore
{
    
template <typename... Args>
void service::start(Args&&... args)
{
    // dlopen
    // dlsym

    // _ptr_info()
    // _ptr_init()
    // _ptr_run()
}

template <typename... Args>
void service::stop(Args&&... args)
{
    // _ptr_exit
    // dlclose
}

}