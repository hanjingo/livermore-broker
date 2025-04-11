#include "tcp_gate.h"

#include <libcpp/util/uuid.hpp>
#include <libcpp/log/logger.hpp>
#include <libcpp/hardware/cpu.h>

namespace broadcast
{

void tcp_gate::init(int port, 
                    int msg_pool_sz, 
                    int cpu_core)
{
    if (_running.load())
        return;

    _port = port;
    _cpu_core = cpu_core;
    for (std::uint16_t id = msg_id_start; id < msg_id_end; id++)
    {
        for (int i = 0; i < msg_pool_sz; ++i)
        {
            _make_json_msg(id);
        }
    }
}

void tcp_gate::run()
{
    if (is_running())
        return;

    _running.store(true);
    listen();

    std::thread([this](){
        if (this->_cpu_core > -1 && !cpu_bind(_cpu_core))
        {
            LOG_ERROR("tcp_gate bind cpu core {} fail", _cpu_core);
            return;
        }

        while(this->is_running())
            this->consume();
    }).detach();
}

void tcp_gate::listen()
{
    if (_running.load() || _port < 1)
        return;

    _running.store(true);
    _li.async_accept(_port, std::bind(&tcp_gate::_async_accept, this, std::placeholders::_1, std::placeholders::_2));
    _io.run();
    LOG_DEBUG("tcp_gate listen on port {}", _port);
}

void tcp_gate::close()
{
    if (!is_running())
        return;

    _running.store(false);
    _io.stop();
    _li.close();
    _mgr.range([](libcpp::tcp_conn::conn_ptr_t const& conn, std::set<common::market_data_shm*>& mds) -> bool {
        if (conn != nullptr)
            conn->close();
        delete conn;
        return true;
    });
    _mgr.clear();
    LOG_DEBUG("tcp_gate closed");
} 

void tcp_gate::consume()
{
    _mgr.range([this](libcpp::tcp_conn::conn_ptr_t const& conn, std::set<common::market_data_shm*>& mds) -> bool {
        if (conn == nullptr)
            return true;
        if (mds.empty())
            return true;
         
        for(auto md : mds)
        {
            if (md == nullptr || md->flag() == nullptr || md->data() == nullptr)
                continue;

            if (!md->readable())
                continue;

            if (!md->consume())
                continue;

            auto msg = this->_pop_json_msg(msg_id_md_ntf);
            while (msg == nullptr) 
            {
                this->_make_json_msg(msg_id_md_ntf);
                msg = this->_pop_json_msg(msg_id_md_ntf);
            }

            common::md_util::to_json(md->data(), msg->payload);
            LOG_DEBUG("read market data from shared memory {}", common::md_util::fmt(md->data()));
            
            conn->async_send(msg);
            LOG_DEBUG("tcp_gate send msg->size()={}", msg->size());
        }
        return true;
    });
}

void tcp_gate::subscribe(libcpp::tcp_conn::conn_ptr_t conn, std::vector<std::string>& codes)
{
    std::set<common::market_data_shm*> mds;
    auto bfind = _mgr.find(std::move(conn), mds);
    for (auto code : codes)
    {
        auto md = new common::market_data_shm(code);
        mds.insert(md);
    }
    
    if (bfind)
        _mgr.replace(std::move(conn), std::move(mds));
    else 
        _mgr.insert(std::move(conn), std::move(mds));
}

void tcp_gate::unsubscribe(libcpp::tcp_conn::conn_ptr_t conn, std::vector<std::string>& codes)
{
    std::set<common::market_data_shm*> mds;
    auto bfind = _mgr.find(std::move(conn), mds);
    if (!bfind)
        return;

    for (auto code : codes)
    {
        for (auto itr = mds.begin(); itr != mds.end(); ++itr)
        {
            if ((*itr)->data() == nullptr)
                continue;
            if ((*itr)->data()->instrument_id != code)
                continue;
            delete *itr;
            itr = mds.erase(itr);
        }
    }
    if (mds.empty())
        _mgr.erase(std::move(conn));
    else
        _mgr.replace(std::move(conn), std::move(mds));
}

void tcp_gate::_async_accept(const libcpp::tcp_listener::err_t& err, libcpp::tcp_socket* sock)
{
    if (err.failed())
    {
        LOG_ERROR("tcp_gate::listen accept fail");
        if (sock != nullptr)
            delete sock;
        return;
    }

    sock->set_option(libcpp::tcp_socket::opt_no_delay(true));
    auto conn = new libcpp::tcp_conn(_io, sock);
    if (conn == nullptr)
    {
        LOG_ERROR("tcp_gate create conn fail");
        if (sock != nullptr)
            delete sock;
        return;
    }

    conn->set_recv_handler(std::bind(&tcp_gate::_on_conn_recv, this, std::placeholders::_1, std::placeholders::_2));
    conn->set_disconnect_handler(std::bind(&tcp_gate::_on_conn_disconnect, this, std::placeholders::_1));
    std::set<common::market_data_shm*> mds;
    _mgr.emplace(std::move(conn), std::move(mds));

    // start async accept again
    _li.async_accept(_port, std::bind(&tcp_gate::_async_accept, this, std::placeholders::_1, std::placeholders::_2));
}

void tcp_gate::_on_conn_send(libcpp::tcp_conn::conn_ptr_t conn, libcpp::tcp_conn::msg_ptr_t msg)
{
    LOG_DEBUG("tcp_gate send");
    if (conn == nullptr || msg == nullptr)
        return;
    
    _recycle_msg(msg);
}

void tcp_gate::_on_conn_recv(libcpp::tcp_conn::conn_ptr_t conn, libcpp::tcp_conn::msg_ptr_t msg)
{
    LOG_DEBUG("tcp_gate recv");
    if (conn == nullptr || msg == nullptr)
        return;
    
    _recycle_msg(msg);
}

void tcp_gate::_on_conn_disconnect(libcpp::tcp_conn::conn_ptr_t conn)
{
    if (conn == nullptr)
        return;

    LOG_DEBUG("tcp_gate disconnect");
    _mgr.erase(std::move(conn));
    conn->close();
    delete conn;
}

void tcp_gate::_recycle_msg(libcpp::tcp_conn::msg_ptr_t arg)
{
    if (arg == nullptr)
        return;

    auto msg = static_cast<json_msg*>(arg);
    _msg_pool[msg->id].push(msg);
}

std::size_t tcp_gate::_make_json_msg(const std::uint16_t id)
{
    _msg_pool[id].construct(id);
    return _msg_pool[id].size();
}

json_msg* tcp_gate::_pop_json_msg(const std::uint16_t id)
{
    return _msg_pool[id].pop();
}

}// namespace broadcast