#include <string>
#include <iostream>

#include <libcpp/testing/exception.hpp>
#include <libcpp/os/dll.h>
#include <libcpp/os/env.h>
#include <libcpp/os/application.hpp>

#include "common/error_base.h"
#include "service.h"

using namespace livermore;

int main(int argc, char* argv[])
{
    // get env
    libcpp::options opt;
    opt.add<std::string>("module", std::string("manage"));
    std::string module = opt.parse<std::string>(argc, argv, "module");

    // start service
    livermore::service serv{};
    auto dll = std::string("lib").append(module).append(DLL_EXT);

    err_t err = serv.load(dll.c_str());
    libcpp::throw_if_false(err == common::error::ok, 
        std::string("load service ").append(dll).append(" fail, with error code=").append(std::to_string(static_cast<int>(err))).c_str());

    err = serv.init();
    libcpp::throw_if_false(err == common::error::ok, 
        std::string("init service ").append(dll).append(" fail, with error code=").append(std::to_string(static_cast<int>(err))).c_str());

    err = serv.start();
    libcpp::throw_if_false(err == common::error::ok, 
        std::string("start service ").append(dll).append(" fail, with error code=").append(std::to_string(static_cast<int>(err))).c_str());

    return 0;
}