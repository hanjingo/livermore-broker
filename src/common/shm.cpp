#include "market_data_util.h"
#include <libcpp/util/string_util.hpp>

namespace common
{
template <typename T>
bool shm<T>::write(const std::size_t nconsum)
{
    if (data() == nullptr || flag() == nullptr)
        return false;
    
    *(flag()) += nconsum;
    return true;
}

template <typename T>
bool shm<T>::write(const T* arg, const std::size_t nconsum)
{
    if (data() == nullptr || flag() == nullptr)
        return false;

    *(data()) = arg;
    *(flag()) += nconsum;
    return true;
}

template <typename T>
bool shm<T>::read()
{
    if (data() == nullptr || flag() == nullptr)
        return false;
    
    return true;
}

template <typename T>
bool shm<T>::read(T* arg)
{
    if (data() == nullptr || flag() == nullptr)
        return false;
        
    *arg = *(data());
    return true;
}

template <typename T>
bool shm<T>::consume()
{
    if (data() == nullptr || flag() == nullptr || *(flag()) < 1)
        return false;
    
    *(flag()) -= 1;
    return true;
}

template <typename T>
bool shm<T>::consume(T* arg)
{
    if (data() == nullptr || flag() == nullptr || *(flag()) < 1)
        return false;
        
    *(flag()) -= 1;
    *arg() = *(data());
    return true;
}

}