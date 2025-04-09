#include "tcp_gate.h"
#include "api_json.h"

#include <libcpp/util/uuid.hpp>
#include <libcpp/log/logger.hpp>

namespace broadcast
{

void tcp_gate::init()
{
    if (_running.load())
        return;

    for (auto id = common::msg_id_start; id < common::msg_id_end; ++id)
    {
        objs[id].construct(id, 0, 0, 0, 0, common::encode_json, NULL);
    }
}

void tcp_gate::listen(const std::uint16_t port)
{
    if (_running.load())
        return;

    _running.store(true);
    _li.async_accept(port, std::bind(&tcp_gate::_async_accept, this, std::placeholders::_1, std::placeholders::_2));
    _io.run();
}

void tcp_gate::close()
{
    if (!_running.load())
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
    _mgr.range([](libcpp::tcp_conn::conn_ptr_t const& conn, std::set<common::market_data_shm*>& mds) -> bool {
        if (conn == nullptr)
            return true;
        if (mds.empty())
            return true;
        
        api::json::md_ntf* ntf = _obj[msg_id_md_ntf].pop();
        while (ntf == nullptr)
        {
            _obj[msg_id_md_ntf].construct(msg_id_md_ntf, 0, 0, 0, 0, common::encode_json, NULL);
            ntf = _obj[msg_id_md_ntf].pop();
            LOG_DEBUG("create obj: md_ntf");
        }
        for(auto md : mds)
        {
            if (md == nullptr || md->flag == nullptr || md->data == nullptr)
                continue;

            md->read();
            if (*(md->flag) == 0)
                continue;

            ntf.payload.push_back(md);
            LOG_DEBUG("read market data from shared memory {}", md->fmt());
        }
        conn->async_send(&ntf);
        LOG_DEBUG("tcp_gate send ntf.payload.size()={}", ntf.payload.size());
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
            if ((*itr)->data == nullptr)
                continue;
            if ((*itr)->data->instrument_id != code)
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
}

void tcp_gate::_on_conn_send(libcpp::tcp_conn::conn_ptr_t conn, libcpp::tcp_conn::msg_ptr_t msg)
{
    LOG_DEBUG("tcp_gate send");
    if (conn == nullptr || msg == nullptr)
        return;
    
    uint16_t id;
    _objs[id].push(msg);
}

void tcp_gate::_on_conn_recv(libcpp::tcp_conn::conn_ptr_t conn, libcpp::tcp_conn::msg_ptr_t msg)
{
    LOG_DEBUG("tcp_gate recv");
    if (conn == nullptr || msg == nullptr)
        return;
    
    uint16_t id;
    _objs[id].push(msg);
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

}// namespace broadcast