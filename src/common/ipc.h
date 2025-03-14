#ifndef IPC_HPP
#define IPC_HPP

#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

namespace common
{

class ipc
{
public:
    ipc();
    ~ipc();

    template<typename Container>
    Container make(const char* id);

    template<typename Container>
    void free(const char* id, Container container);

    void read();

    void write();
};

}

#endif