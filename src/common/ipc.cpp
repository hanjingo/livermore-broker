#include "ipc.h"

namespace common
{

ipc ipc::make(const char* id, const std::size_t sz, const int flag)
{
    libcpp::shared_memory::remove(id);
    return common::ipc(id, sz, flag);
}

void ipc::read(char* buf, std::size_t sz)
{
    char* tmp;
    _rch << static_cast<char*>(_shm.addr());
    _rch >> tmp;
    memcpy(buf, tmp, sz);
}

void ipc::write(char* buf, std::size_t sz)
{
    char* tmp;
    _wch << buf;
    _wch >> tmp;
    memcpy(static_cast<char*>(_shm.addr()), tmp, sz);
}

}