#ifndef APPLICATION_H
#define APPLICATION_H

#define DEPTH_MARKET_DATA

#include <unordered_map>

#include "version.h"
#include "error.h"
#include "config.h"
#include "application_base.h"
#include "tcp_gate.h"

namespace broadcast
{

class application : public common::application_base
{
public:
    application() : common::application_base() { };
    ~application() {};
    application(const application&) = delete;
    application& operator=(const application&) = delete;

    static application& instance();

    err_t init();
    err_t run() override;
    err_t stop() override;

    broadcast::config                                       conf;
    std::unordered_map<std::uint16_t, broadcast::tcp_gate*> tcp_gates;
};

}

#endif