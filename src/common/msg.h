#ifndef MSG_H
#define MSG_H

#include <cstdint>
#include <atomic>
#include <libcpp/net/proto/message.hpp>

namespace common
{

enum encoding : std::uint8_t
{
    encode_none = 0x0,
    encode_fbs,  // flatbuffers
    encode_json, // json
    encode_pb,   // protobuf
};

template <typename T>
struct msg : public libcpp::message
{
    msg(const uint16_t _id, const uint16_t _len, const uint16_t _seq, const uint16_t _tm, 
        const uint16_t _crc, const encoding _ec) 
        : id{_id}
        , len{_len}
        , seq{_seq}
        , time{_tm}
        , crc16{_crc}
        , encode_type{_ec}
    {}
    ~msg() {}
    virtual std::size_t size() { return len; }
    virtual std::size_t encode(unsigned char* buf, const std::size_t len) { return len; }
    virtual std::size_t decode(const unsigned char* buf, const std::size_t len) { return len; }

    uint16_t id;
    uint16_t len;
    uint32_t seq;
    uint16_t time;
    uint16_t crc16;
    encoding encode_type;
    T payload;
};

}

#endif