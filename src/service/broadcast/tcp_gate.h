#ifndef TCP_GATE_H
#define TCP_GATE_H

#include <atomic>
#include <string>
#include <set>
#include <vector>
#include <unordered_map>

#include <libcpp/net/tcp/tcp_listener.hpp>
#include <libcpp/net/tcp/tcp_conn.hpp>
#include <libcpp/sync/safe_map.hpp>
#include <libcpp/sync/object_pool.hpp>

#include "msg_id.h"
#include "market_data_util.h"
#include "json_msg.h"

namespace broadcast
{

class tcp_gate
{
public:
    using json_obj_pool_t = libcpp::object_pool<json_msg>;

public:
    tcp_gate()
        : _io{}
        , _li{_io}
    {
    }
    ~tcp_gate()
    {
        close();
    }

    inline bool is_running() const { return _running.load(); }
    void init(int port, int msg_pool_sz = 1, int cpu_core = -1);
    void run();
    void listen();
    void close();
    void consume();
    void subscribe(libcpp::tcp_conn::conn_ptr_t conn, std::vector<std::string>& codes);
    void unsubscribe(libcpp::tcp_conn::conn_ptr_t conn, std::vector<std::string>& codes);

private:
    void _async_accept(const libcpp::tcp_listener::err_t& err, libcpp::tcp_socket* sock);
    void _on_conn_send(libcpp::tcp_conn::conn_ptr_t conn, libcpp::tcp_conn::msg_ptr_t msg);
    void _on_conn_recv(libcpp::tcp_conn::conn_ptr_t conn, libcpp::tcp_conn::msg_ptr_t msg);
    void _on_conn_disconnect(libcpp::tcp_conn::conn_ptr_t conn);
    void _recycle_msg(libcpp::tcp_conn::msg_ptr_t msg);
    std::size_t _make_json_msg(const std::uint16_t id);
    json_msg* _pop_json_msg(const std::uint16_t id);

private:
    std::atomic<bool> _running{false};

    libcpp::tcp_listener::io_t _io;
    libcpp::tcp_listener _li;
    libcpp::safe_map<libcpp::tcp_conn::conn_ptr_t, std::set<common::market_data_shm*> > _mgr;
    int _cpu_core{-1};
    int _port{0};

private:
    std::unordered_map<std::uint16_t, json_obj_pool_t> _msg_pool;
};

}

#endif