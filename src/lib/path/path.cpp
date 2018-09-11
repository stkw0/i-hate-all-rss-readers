#include <stdexcept>

#include "env.hpp"
#include "path.hpp"

const std::string GetHome() {
    static std::string home = iharr::getenv("HOME");
    return home;
}

const std::string Expand(std::string&& file) {
    auto pos = file.find('~');
    if(pos != std::string::npos) {
        file.erase(pos, 1);
        file.insert(pos, GetHome());
    }

    return file;
}