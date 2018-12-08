#include <yaml-cpp/yaml.h>

#include "config.hpp"

Config::Config(const std::string& f_name) : BaseConfig(f_name) {
    load();
}

// Save possibly changes
Config::~Config() {
    store();
}

const std::string Config::getDBPath() const {
    return opt.db_path;
}

// Private methods
void Config::load() {
    loadFile();

    opt.db_path = getVal<std::string>("db", "");
}

void Config::store() {
    auto cfg = getYamlCfg();

    cfg["db"] = opt.db_path;

    dumpToFile();
}