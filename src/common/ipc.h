#ifndef IPC_HPP
#define IPC_HPP

#include <libcpp/sync/shared_memory.hpp>
#include <libcpp/sync/chan.hpp>

namespace common
{

class ipc
{
public:
    ipc(const char* id, const std::size_t sz, const int flag = O_CREAT | O_RDWR) 
        : _shm{libcpp::shared_memory(id, sz, flag, 0666)} 
    {
        if (_shm.map() == nullptr)
            throw "create/open ipc fail";
    }
    ~ipc() {};

    static ipc<T> make(const char* id);

    void read(char* buf, std::size_t sz);

    void write(char* buf, std::size sz);

private:
    libcpp::chan<char*> _rch;
    libcpp::chan<char*> _wch;
    libcpp::shared_memory _shm;
};

}

#endif