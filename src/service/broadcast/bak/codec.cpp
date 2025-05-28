#include "codec.h"

template <typename T>
void codec::_recycle_msg(libcpp::tcp_conn::msg_ptr_t arg)
{
    if (arg == nullptr)
        return;

    auto msg = static_cast<T*>(arg);
    _msg_pool[msg->id].push(msg);
}

template <typename T>
std::size_t codec::_make_msg(const std::uint16_t id)
{
    _msg_pool[id].construct(id);
    return _msg_pool[id].size();
}

template <typename T>
libcpp::tcp_conn::msg_ptr_t codec::_pop_msg(const std::uint16_t id)
{
    return _msg_pool[id].pop();
}