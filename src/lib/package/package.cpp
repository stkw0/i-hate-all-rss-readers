#include "package.hpp"

Package::Package(const std::string& s)
    : _p(json::parse(s)), _cmd(_p["command"]) {
    // bug on nlohmann json
    args_t tmp = _p["args"];
    _args = tmp;
}

const std::string Package::command() const {
    return _cmd;
}

const args_t Package::args() const {
    return _args;
}

void Package::answer(const std::string& a) {
    _answer = a;
}
