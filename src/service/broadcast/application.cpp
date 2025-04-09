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

err_t application::init()
{
    LOG_DEBUG("broadcast application::init() enter");
    // load our config
    conf.module = MODULE;
    err_t err = conf.load("livermore-broker.ini");
    if (err != error::ok)
        return err;

    // super init
    err = common::application_base::init(conf);
    if (err != error::ok)
        return err;

    // add water mark
    LOG_INFO("livermore-broadcast");
    LOG_INFO("livermore-broadcast {}.{}.{}", 
        BROADCAST_MAJOR_VERSION, 
        BROADCAST_MINOR_VERSION, 
        BROADCAST_PATCH_VERSION);
    LOG_INFO("livermore-broadcast compile time {}", COMPILE_TIME);
    LOG_INFO("livermore-broadcast email {}", "hehehunanchina@live.com");

    // // init tcp gate
    // for (auto port : conf.tcp_ports)
    // {
    //     auto gate = new tcp_gate();
    //     if (gate == nullptr)
    //         return error::tcp_gate_create_fail;

    //     gate->listen(port);
    //     tcp_gates.emplace(port, gate);
    // }

    return error::ok;
}

err_t application::run()
{
    LOG_DEBUG("broadcast application::run() enter");
    while (true)
    {
        // run tcp gates
        int ngate = 0;
        // for (auto itr = tcp_gates.begin(); itr != tcp_gates.end(); ++itr, ngate++)
        // {
        //     auto port = itr->first;
        //     auto gate = itr->second;
        //     if (gate == nullptr || gate->is_running())
        //         continue;

        //     // run tcp gate in a new thread
        //     int core = conf.cpu_cores.size() > ngate ? conf.cpu_cores[ngate] : -1;
        //     std::thread([port, gate, core](){
        //         LOG_INFO("tcp gate listen on port {}", port);
        //         // bind cpu core
        //         if (core != -1 && !cpu_bind(core))
        //         {
        //             LOG_ERROR("tcp gate bind cpu core {} fail", core);
        //             return;
        //         }
        //         gate->listen(port);
        //     }).detach();
        // }

        // run udp gates
        // TODO
    }

    return error::ok;
}

err_t application::stop()
{
    // for (auto itr = tcp_gates.begin(); itr != tcp_gates.end(); ++itr)
    // {
    //     if (itr->second == nullptr)
    //         continue;

    //     itr->second->close();
    //     delete itr->second;
    //     itr->second = nullptr;
    // }

    common::application_base::stop();
    return error::ok;
}

}