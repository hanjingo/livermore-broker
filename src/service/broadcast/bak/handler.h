#ifndef HANDLER_H
#define HANDLER_H

#include <libcpp/net/tcp/tcp_listener.hpp>
#include <libcpp/net/tcp/tcp_conn.hpp>

class handler
{
public:
    handler() = default;
    ~handler() = default;

private:
    void _on_conn_send(libcpp::tcp_conn::conn_ptr_t conn, libcpp::tcp_conn::msg_ptr_t msg);
    void _on_conn_recv(libcpp::tcp_conn::conn_ptr_t conn, libcpp::tcp_conn::msg_ptr_t msg);
    void _on_conn_disconnect(libcpp::tcp_conn::conn_ptr_t conn);

private:
    libcpp::tcp_conn::conn_ptr_t _conn;

    int _cpu_core{-1};
    int _port{0};
};

#endif