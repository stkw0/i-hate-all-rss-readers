#pragma once

#include <yaml-cpp/yaml.h>

#include "lib/path/path.hpp"


static const std::string CONFIG_FOLDER = Expand("~/.config/iharr/");

class BaseConfig {
public:
	BaseConfig(const std::string& f_name);
	virtual ~BaseConfig() =default;

protected:
	virtual void load() = 0;
	virtual void store() = 0;

	void loadFile();
	void dumpToFile();

	const YAML::Node& getYamlCfg() const;


	// Template methods
	template<typename T>
	T getVal(const std::string& key, const T& default_value) {
    if(auto e = _yaml_cfg[key])
        return e.as<T>();
    else
        return default_value;
	}

	template<typename T>
	T getVal(const std::string& key) {
    return _yaml_cfg[key].as<T>();
	}

private:
	YAML::Node _yaml_cfg;
	const std::string _file_name;
};