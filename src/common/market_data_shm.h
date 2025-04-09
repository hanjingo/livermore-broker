#ifndef MARKET_DATA_SHM_H
#define MARKET_DATA_SHM_H

#include <libcpp/sync/shared_memory.hpp>

#include "market_data.h"

#include <string>

namespace common
{

struct market_data_shm
{
    market_data_shm(std::string code) 
        : shm_data{libcpp::shared_memory(code.c_str(), sizeof(market_data))}
        , shm_flag{libcpp::shared_memory(code.append("_readable").c_str(), sizeof(std::uint8_t))}
    {
        shm_data.map();
        data = static_cast<market_data*>(shm_data.addr());

        shm_flag.map();
        flag = static_cast<std::uint8_t*>(shm_flag.addr());
    }
    ~market_data_shm() 
    {}

    market_data* data;
    std::uint8_t* flag;

    libcpp::shared_memory shm_data;
    libcpp::shared_memory shm_flag;

    static void copy_from(market_data* dst, const market_data* src);

    void reset();
    std::string fmt();
    bool is_equal(const market_data_shm* rhs, std::string& memo);
    void write(market_data* md = nullptr);
    void read(market_data* md = nullptr);
};

}

#endif