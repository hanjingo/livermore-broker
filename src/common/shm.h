#ifndef SHM_H
#define SHM_H

#include <atomic>
#include <libcpp/sync/shared_memory.hpp>

#include <string>

namespace common
{

template <typename T>
struct shm
{
    shm(std::string code, const std::size_t sz = sizeof(T)) 
        : _shm_data{libcpp::shared_memory(code.c_str(), sz)}
        , _shm_flag{libcpp::shared_memory(code.append("_readable").c_str(), sizeof(std::int64_t))}
    {
        if (_shm_data.map() == nullptr)
        {
            throw std::runtime_error("shm map data failed");
        }
        if (_shm_flag.map() == nullptr)
        {
            throw std::runtime_error("shm map flag failed");
        }
    }
    ~shm() 
    {
    }

    inline T* data() { return static_cast<T*>(_shm_data.addr()); }
    inline std::int64_t* flag() { return static_cast<std::int64_t*>(_shm_flag.addr()); }
    inline bool readable() { return *(flag()) > 0; }

    bool write(const std::size_t nconsum = 1);
    bool write(const T* arg, const std::size_t nconsum = 1);

    bool read();
    bool read(T* arg);

    bool consume();
    bool consume(T* arg);

private:
    libcpp::shared_memory _shm_data;
    libcpp::shared_memory _shm_flag;
};

}

#endif