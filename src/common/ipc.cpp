#include "ipc.h"

    // // [shared memory] single byte model
    // boost::interprocess::shared_memory_object::remove("mem");
    // boost::interprocess::shared_memory_object mem(boost::interprocess::open_or_create, 
    //                                               "mem", 
    //                                               boost::interprocess::read_write);
    // mem.truncate(1024);
    // boost::interprocess::offset_t sz;
    // if (mem.get_size(sz))
    //     std::cout << mem.get_name() << ":" << sz << std::endl;

    // boost::interprocess::mapped_region rg1(mem, boost::interprocess::read_write);
    // int *addr = static_cast<int*>(rg1.get_address());
    // *addr = 123;

    // boost::interprocess::mapped_region rg2(mem, boost::interprocess::read_write);
    // int *ptr2 = static_cast<int*>(rg2.get_address());
    // std::cout << *ptr2 << std::endl;


namespace common
{

ipc::ipc()
{

};

ipc::~ipc()
{

};

template<typename Container>
Container ipc::make(const char* id)
{
    boost::interprocess::shared_memory_object mem()
}

template<typename Container>
void ipc::free(const char* id, Container container)
{

}

void ipc::read()
{

}

void ipc::write()
{

}

}