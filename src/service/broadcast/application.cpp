#include "application.h"

#include <libcpp/io/filepath.hpp>
#include <libcpp/os/env.h>
#include <libcpp/hardware/cpu.h>

namespace broadcast
{

application& application::instance()
{
    static application inst;
    return inst;
}    

err_t application::init(const char* id)
{
    LOG_DEBUG("broadcast application::init() enter");
    // load our config
    conf.name = std::string(id);
    err_t err = conf.load("livermore-broker.ini");
    if (err != error::ok)
        return err;

    // super init
    err = common::application_base::init(conf);
    if (err != error::ok)
        return err;

    // add water mark
    LOG_INFO("livermore-broadcast {}", conf.name);
    LOG_INFO("livermore-broadcast {}.{}.{}", 
        BROADCAST_MAJOR_VERSION, 
        BROADCAST_MINOR_VERSION, 
        BROADCAST_PATCH_VERSION);
    LOG_INFO("livermore-broadcast compile time {}", COMPILE_TIME);
    LOG_INFO("livermore-broadcast email {}", "hehehunanchina@live.com");

    // init tcp gate
    for (auto port : conf.tcp_ports)
    {
        auto gate = new tcp_gate();
        if (gate == nullptr)
            return error::tcp_gate_create_fail;

        int core = -1;
        if (!conf.bind_cpu_cores.empty())
        {
            core = conf.bind_cpu_cores.front();
            conf.bind_cpu_cores.erase(conf.bind_cpu_cores.begin());
        }
        gate->init(port, conf.msg_pool_size, core);
        tcp_gates.emplace(port, gate);
    }

    return error::ok;
}

err_t application::run()
{
    LOG_DEBUG("broadcast application::run() enter");

    // run tcp gates
    while (true)
    {
        // run tcp gates
        for (auto itr = tcp_gates.begin(); itr != tcp_gates.end(); ++itr)
        {
            if (itr->second == nullptr)
                continue;
            
            // run
            itr->second->run();
        }

        // run udp gates
        // TODO

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return error::ok;
}

err_t application::stop()
{
    for (auto itr = tcp_gates.begin(); itr != tcp_gates.end(); ++itr)
    {
        if (itr->second == nullptr)
            continue;

        itr->second->close();
        delete itr->second;
        itr->second = nullptr;
    }

    common::application_base::stop();
    return error::ok;
}

}