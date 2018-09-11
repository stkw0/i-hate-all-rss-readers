#pragma once

#include <memory>
#include <string>

#include <spdlog/spdlog.h>

using spdlogger = std::shared_ptr<spdlog::logger>;

spdlogger NewLogger(const std::string& name);