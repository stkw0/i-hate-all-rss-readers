#include <fstream>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include "config.hpp"

using namespace boost::filesystem;

BaseConfig::BaseConfig(const std::string& f_name)
    : _file_name(f_name + ".yml") {
    path dir(CONFIG_FOLDER);
    if(!exists(dir) && !create_directory(dir))
        throw std::runtime_error("Could not create config directory");
}

// Protected methods
void BaseConfig::loadFile() {
    static auto file_path = CONFIG_FOLDER + _file_name;
    if(!exists(file_path)) store();

    _yaml_cfg = YAML::LoadFile(CONFIG_FOLDER + _file_name);
}

void BaseConfig::dumpToFile() {
    static auto file_path = CONFIG_FOLDER + _file_name;

    std::ofstream config_file(CONFIG_FOLDER + _file_name);
    config_file << _yaml_cfg;
}

const YAML::Node& BaseConfig::getYamlCfg() const {
    return _yaml_cfg;
}
