#include "logging.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

spdlogger NewLogger(const std::string& name) {
    {
        auto logger = spdlog::get(name);
        spdlog::set_level(spdlog::level::debug);
        if(logger != nullptr) return logger;
    }

    return spdlog::stdout_color_mt(name);
}