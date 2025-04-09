#ifndef MSG_H
#define MSG_H

#include <cstdint>
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

template<typename T>
struct msg : public libcpp::message
{
    msg(const uint16_t _id, const uint16_t _len, const uint16_t _seq, const uint16_t _tm, 
        const uint16_t _crc, const encoding _ec, const T& _payload) 
        : id{_id}
        , len{_len}
        , seq{_seq}
        , time{_tm}
        , crc16{_crc}
        , encode_type{_ec}
        , payload{_payload}
    {}
    ~msg() {}
    virtual std::size_t size() { return len; }
    virtual std::size_t encode(unsigned char* buf, const std::size_t len) { return len; }
    virtual std::size_t decode(const unsigned char* buf, const std::size_t len) { return len; }

    inline std::size_t head_len() { return 15; }
    inline uint16_t inc() { return seq++; }

    uint16_t id;
    uint16_t len;
    uint32_t seq;
    uint16_t time;
    uint16_t crc16;
    encoding encode_type;
    T payload;
};

}

// #define FBS_API(id, name) \
//     struct #name : public common::msg<fbs::#name> \
//     { \
//         #name() : msg(#id, 0, 0, 0, common::msg::encode_fbs, fbs::Create##name()) {} \
//         ~#name() {} \
//         std::size_t size() override { return len;} \
//         std::size_t encode(char* buf, std::size_t size) override \
//         { \
//             if (size < head_len()) \
//                 return 0; \
//             fbs::#name##Builder builder_(size); \
//             builder_.Finish(data); \
//             len = builder_.GetSize() + head_len(); \
//             if (size < len) \
//                 return 0; \
//             memcpy(buf + head_len(), builder_.GetBufferPointer(), builder_.GetSize()); \
//             return msg::encode(buf, size); \
//         } \
//         std::size_t decode(const char* buf, std::size_t size) override \
//         { \
//             if (msg::decode(buf, size) == 0) \
//                 return 0; \
//             data = fbs::Get##name(buf + head_len()); \
//             return data == nullptr ? 0 : data->size(); \
//         } \
//     }; \

#endif