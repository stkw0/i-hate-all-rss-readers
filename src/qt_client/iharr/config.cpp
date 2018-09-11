#include <yaml-cpp/yaml.h>

#include "config.hpp"

Config::Config(const std::string& f_name) : BaseConfig(f_name) {
    load();
}

// Save possibly changes
Config::~Config() {
    store();
}

const QString Config::getPassword() const {
    return QString::fromStdString(opt.password);
}

void Config::setPassword(const QString& p) {
    opt.password = p.toStdString();
}

const QString Config::getUsername() const {
    return QString::fromStdString(opt.username);
}

void Config::setUsername(const QString& u) {
    opt.username = u.toStdString();
}

const QString Config::getEmail() const {
    return QString::fromStdString(opt.email);
}

void Config::setEmail(const QString& e) {
    opt.email = e.toStdString();
}

// Private methods
void Config::load() {
    loadFile();

    opt.password = getVal<std::string>("password", "");
    opt.username = getVal<std::string>("user", "");
    opt.email = getVal<std::string>("email", "");
}

void Config::store() {
    auto cfg = getYamlCfg();

    cfg["password"] = opt.password;
    cfg["user"] = opt.username;
    cfg["email"] = opt.email;

    dumpToFile();
}