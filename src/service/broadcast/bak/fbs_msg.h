#ifndef FBS_MSG_H
#define FBS_MSG_H

#include <libcpp/log/logger.hpp>

#include "msg.h"
#include "market_data_generated.h"

namespace broadcast::fbs
{

using md_ntf_t = common::msg<broadcast::md_ntf>;

template <typename T>
struct fbs_msg : public common::msg<T>
{
    fbs_msg(const uint16_t _id)
        : common::msg<T>(_id, 0, 0, 0, 0, common::encode_fbs)
    {}
    ~fbs_msg() {}
    virtual std::size_t size() override 
    {
        return payload.Finish();
    }
    virtual std::size_t encode(unsigned char* buf, const std::size_t size) override
    {
        flatbuffers::FlatBufferBuilder fbb;
        fbb.Finish(payload);
        std::size_t sz = fbb.GetSize();
        memcpy(buf, fbb.GetBufferPointer(), sz);
        return sz;
    }
    virtual std::size_t decode(const unsigned char* buf, const std::size_t size) override 
    {
        // auto verifier = flatbuffers::Verifier(reinterpret_cast<const uint8_t*>(buf), size);
        // if (!payload(verifier)) 
        //     return 0;

        payload.GetVTable(reinterpret_cast<const uint8_t*>(buf));
    }
};

}

#endif