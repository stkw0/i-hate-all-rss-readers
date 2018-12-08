#pragma once

#include "config/config.hpp"


class Config : BaseConfig {
public:
	Config(const std::string& f_name);
	~Config();

	const std::string getDBPath() const;

private:
	void store();
	void load();

	struct Options {
		std::string db_path;
	} opt;
};
