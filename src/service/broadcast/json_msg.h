#ifndef JSON_MSG_H
#define JSON_MSG_H

#include <libcpp/encoding/json.hpp>
#include <libcpp/log/logger.hpp>

#include "msg.h"

namespace broadcast
{
    
struct json_msg : public common::msg<libcpp::json>
{
    json_msg(const uint16_t _id)
        : common::msg<libcpp::json>(_id, 0, 0, 0, 0, common::encode_json)
    {}
    ~json_msg() {}
    virtual std::size_t size() override 
    {
        return payload.size() + 15;
    }

    virtual std::size_t encode(unsigned char* buf, const std::size_t size) override
    { 
        libcpp::json js;
        js["id"] = id;
        js["len"] = 0;
        js["seq"] = seq;
        js["time"] = time;
        js["crc16"] = crc16;
        js["encode_type"] = encode_type;
        js["payload"] = payload;
        js["len"] = js.size();
    
        auto str = js.dump(4);
        LOG_DEBUG("encode md_ntf to str ={}", str);
        if (size < str.size())
            return 0;
        memcpy(buf, str.c_str(), str.size());
        return str.size();
    }

    virtual std::size_t decode(const unsigned char* buf, const std::size_t size) override 
    {
        libcpp::json js = libcpp::json::parse(reinterpret_cast<const char*>(buf));
        len = js["len"];
        if (size < len)
            return 0;

        id = js["id"];
        seq = js["seq"];
        time = js["time"];
        crc16 = js["crc16"];
        encode_type = js["encode_type"];
        payload = js["payload"];
        return len; 
    }
};

}

#endif