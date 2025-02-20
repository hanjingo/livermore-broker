#include <libcpp/testing/crash.hpp>
#include <libcpp/log/log.hpp>
#include <libcpp/io/file.hpp>
#include <libcpp/io/filepath.hpp>
#include <libcpp/os/signal.hpp>
#include <libcpp/os/application.hpp>

#include "version.h"
#include "service.h"

#ifdef _WIN32
bool dump_callback(const wchar_t* dump_dir,
                   const wchar_t* minidump_id,
                   void* context,
                   EXCEPTION_POINTERS* exinfo,
                   MDRawAssertionInfo* assertion,
                   bool succeeded)
{
    return true;
}
#elif __APPLE__
bool dump_callback(const char *dump_dir, const char *minidump_id, void *context, bool succeeded)
{
    return true;
}
#else
bool dump_callback(const google_breakpad::MinidumpDescriptor& descriptor, void* context, bool succeeded)
{
    return true;
}
#endif

int main(int argc, char* argv[])
{
    // add log
    libcpp::logger::instance()->add_sink(libcpp::logger::create_sink("logs/test.log", MB(10), 5, true));
    LOG_INFO("livermore-broker log init.");

    // add crash handler
    libcpp::crash_handler::instance()->prevent_set_unhandled_exception_filter();
    libcpp::crash_handler::instance()->set_dump_callback(dump_callback);
    libcpp::crash_handler::instance()->set_local_path("./");
    LOG_INFO("livermore-broker carsh handler init.");

    // ignore signal
    libcpp::sigcatch({SIGABRT, SIGTERM}, [](int sig){});
    LOG_INFO("livermore-broker ignore signal init.");

    // start service
    // livermore::service::start("database");
    // livermore::service::start("sentinel");
    livermore::service quote{};
    livermore::service::error err = quote.start("./libquote.so");
    if (err != livermore::service::ok)
        LOG_ERROR("start service fail, with error code={0}", (int)(err));
    // livermore::service::start("broadcast");
    // livermore::service::start("manage");

    // get start
    LOG_INFO("livermore-broker started!");
    // libcpp::application::wait();
    return 0;
}