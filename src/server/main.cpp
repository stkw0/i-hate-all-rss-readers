#include <exception>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "iharr.hpp"
#include "lib/logging.hpp"

int main() {
    auto console = NewLogger("main");

    try {
        IHARR iharr;
        iharr.run();
    } catch(std::exception& e) {
        console->critical("Exception on main: {}", e.what());
    } catch(...) {
        console->critical("Unknown exception thrown on main function");
    }
}