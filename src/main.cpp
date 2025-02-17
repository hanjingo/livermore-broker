#include <libcpp/testing/crash.hpp>
#include <libcpp/log/log.hpp>
#include <libcpp/io/fsize.hpp>
#include <libcpp/io/filepath.hpp>
#include <libcpp/os/signal.hpp>

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
    libcpp::logger::instance()->add_sink(libcpp::logger::create_sink("logs/.log", MB(10), 5, true));
    LOG_INFO("livermore-broker log init.");

    // add crash handler
#ifdef _WIN32
    libcpp::prevent_set_unhandled_exception_filter();
#endif
    libcpp::crash_handler::instance()->set_dump_callback(dump_callback);
    libcpp::crash_handler::instance()->set_local_path(libcpp::file_path::pwd());
    LOG_INFO("livermore-broker carsh handler init.");

    // ignore signal
    libcpp::sigcatch(SIGABRT, [](int sig){});
    libcpp::sigcatch(SIGTERM, [](int sig){});

    // get start
    LOG_INFO("livermore-broker start!");
    return 0;
}