#ifndef CODEC_H
#define CODEC_H

#include <libcpp/net/tcp/tcp_conn.hpp>
#include <libcpp/sync/object_pool.hpp>

template <typename T>
class codec
{
public:
    using market_data_shm = common::shm<market_data>;

public:
    codec() = default;
    ~codec() = default;

private:
    void _recycle_msg(libcpp::tcp_conn::msg_ptr_t msg);
    std::size_t _make_msg(const std::uint16_t id);
    libcpp::tcp_conn::msg_ptr_t _pop_msg(const std::uint16_t id);

private:
    libcpp::object_pool<T> _msg_pool;
};

#endif