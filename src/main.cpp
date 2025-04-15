#include <string>
#include <iostream>

#include <libcpp/testing/exception.hpp>
#include <libcpp/os/dll.h>
#include <libcpp/os/env.h>
#include <libcpp/os/application.hpp>

#include "common/error_base.h"
#include "common/config_base.h"
#include "service.h"

using namespace livermore;

int main(int argc, char* argv[])
{
    // get env
    libcpp::options opt;
    opt.add<std::string>("name", std::string("manage"));
    std::string name = opt.parse<std::string>(argc, argv, "name");

    // start service
    livermore::service serv{};
    std::string mod = common::config_base::get_value<std::string>(
        "livermore-broker.ini", name.c_str(), "module");
    libcpp::throw_if_empty(mod, 
        std::string("parse ").append(name).append(" module value fail").c_str());
    auto dll = std::string("lib").append(mod).append(DLL_EXT);

    err_t err = serv.load(dll.c_str());
    libcpp::throw_if_false(err == common::error::ok, 
        std::string("load service ").append(dll).append(" fail, with error code=").append(
            common::err_to_hex(err)).c_str());

    err = serv.init(name.c_str());
    libcpp::throw_if_false(err == common::error::ok, 
        std::string("init service ").append(dll).append(" fail, with error code=").append(
            common::err_to_hex(err)).c_str());

    err = serv.start();
    libcpp::throw_if_false(err == common::error::ok, 
        std::string("start service ").append(dll).append(" fail, with error code=").append(
            common::err_to_hex(err)).c_str());

    return 0;
}