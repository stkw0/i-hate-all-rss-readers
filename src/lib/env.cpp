#include <cstdlib>
#include <stdexcept>

#include <fmt/format.h>

#include "env.hpp"

using namespace fmt::literals;

const std::string iharr::getenv(const char* name) {
    auto var = std::getenv(name);
    if(!var) throw std::runtime_error("{} env var doesn't exist"_format(name));

    return var;
}
