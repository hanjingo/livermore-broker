#include <libcpp/testing/crash.hpp>
#include <libcpp/log/log.hpp>
#include <libcpp/io/file.hpp>
#include <libcpp/io/filepath.hpp>
#include <libcpp/os/signal.hpp>
#include <libcpp/os/application.hpp>
#include <libcpp/encoding/ini.hpp>
#include <libcpp/testing/exception.hpp>
#include <libcpp/testing/error.hpp>
#include <libcpp/strings/string.hpp>
#include <libcpp/os/dll.h>

#include "version.h"
#include "service.h"

int main(int argc, char* argv[])
{
    // get env
    LOG_INFO("livermore-broker env options init.");
    libcpp::options opt;
    opt.add<std::string>("module", std::string("manage"));
    std::string module = opt.parse<std::string>(argc, argv, "module");
    LOG_INFO("get module name={}", module);

    // parse config
    LOG_INFO("livermore-broker config init.");
    libcpp::ini cfg;
    libcpp::throw_if_false(cfg.read_file("livermore-broker.ini"), "parse config fail");
    LOG_INFO("config log_path={}", cfg.get_child(module).get<std::string>("log_path"));
    LOG_INFO("config log_file_size_mb={}", cfg.get_child(module).get<int>("log_file_size_mb"));
    LOG_INFO("config log_file_num={}", cfg.get_child(module).get<int>("log_file_num"));
    LOG_INFO("config log_file_rotate_on_open={}", cfg.get_child(module).get<bool>("log_file_rotate_on_open"));
    LOG_INFO("config log_min_lvl={}", cfg.get_child(module).get<int>("log_min_lvl", 1));
    LOG_INFO("config crash_path={}", cfg.get_child(module).get<std::string>("crash_path"));

    // add log
    LOG_INFO("livermore-broker log init.");
    libcpp::logger::instance()->add_sink(libcpp::logger::create_sink(
        cfg.get_child(module).get<std::string>("log_path"), 
        MB(cfg.get_child(module).get<int>("log_file_size_mb")), 
        cfg.get_child(module).get<int>("log_file_num"), 
        cfg.get_child(module).get<bool>("log_file_rotate_on_open")));
    libcpp::logger::instance()->set_level(
        (libcpp::log_lvl)(cfg.get_child(module).get<int>("log_min_lvl", 1)));

    // add crash handler
    LOG_INFO("livermore-broker carsh handler init.");
    libcpp::crash_handler::instance()->prevent_set_unhandled_exception_filter();
    libcpp::crash_handler::instance()->set_local_path(cfg.get_child(module).get<std::string>("crash_path"));
    LOG_INFO("livermore-broker crash set local path={}", cfg.get_child(module).get<std::string>("crash_path"));

    // ignore signal
    LOG_INFO("livermore-broker signal init.");
    libcpp::sigcatch({SIGABRT, SIGTERM}, [](int sig){});

    // start service
    LOG_INFO("livermore-broker server init.");
    livermore::service serv{};
    auto dll = libcpp::string::fmt("./{}{}{}", "lib", module, DLL_EXT);
    LOG_DEBUG("load dll {}", dll);
    // livermore::error_t err = serv.start(dll.c_str());
    // libcpp::throw_if_not_equal(err, livermore::ok, 
    //     libcpp::string::fmt("start service fail, with error code={}", err.value()).c_str());

    // get start
    LOG_INFO("livermore-broker started!");
    // libcpp::application::wait();
    return 0;
}