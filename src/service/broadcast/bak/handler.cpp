#include "handler.h"

void handler::_on_conn_send(libcpp::tcp_conn::conn_ptr_t conn, libcpp::tcp_conn::msg_ptr_t msg)
{
    LOG_DEBUG("handler send");
    if (conn == nullptr || msg == nullptr)
        return;
    
    _recycle_msg(msg);
}

void handler::_on_conn_recv(libcpp::tcp_conn::conn_ptr_t conn, libcpp::tcp_conn::msg_ptr_t msg)
{
    LOG_DEBUG("handler recv with");
    if (conn == nullptr || msg == nullptr)
        return;
    
    auto json_msg = static_cast<broadcast::json_msg*>(msg);
    LOG_DEBUG("handler recv json_msg->id={}", json_msg->id);
    switch (json_msg->id)
    {
        case msg_id_md_sub_req:
        {
            // {topics:{"xxx", "xxx"}}
            std::vector<std::string> codes;
            for (auto& code : json_msg->payload["topics"])
                codes.push_back(code);
            subscribe(conn, codes);

            auto rsp = this->_pop_json_msg(msg_id_md_sub_rsp);
            while (rsp == nullptr) 
            {
                this->_make_json_msg(msg_id_md_sub_rsp);
                rsp = this->_pop_json_msg(msg_id_md_sub_rsp);
            }

            libcpp::json js;
            js["result"] = 0;
            js["topics"] = json_msg->payload;
            rsp->payload = js.dump();
            conn->async_send(rsp);
            LOG_DEBUG("handler send rsp msg->size()={}", msg->size());
            break;
        }
        case msg_id_md_unsub_req:
        {
            std::vector<std::string> codes;
            for (auto& code : json_msg->payload)
                codes.push_back(code);
            unsubscribe(conn, codes);
            break;
        }
        default:
            LOG_ERROR("handler recv unknow msg id {}", json_msg->id);
            break;
    }

    // reuse msg
    _recycle_msg(msg);
}

void handler::_on_conn_disconnect(libcpp::tcp_conn::conn_ptr_t conn)
{
    if (conn == nullptr)
        return;

    LOG_DEBUG("handler disconnect");
    _mgr.erase(std::move(conn));
    conn->close();
    delete conn;
}