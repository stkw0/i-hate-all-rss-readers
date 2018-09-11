#pragma once

#include <unordered_map>
#include <string>

#include <nlohmann/json.hpp>

using args_t = std::unordered_map<std::string, std::string>;
using json = nlohmann::json;

class Package {

public:
	Package(const std::string& s);

	const std::string command() const;
	const args_t args() const;

	void answer(const std::string& a);

private:
	json _p;

	const std::string _cmd;
	args_t _args;

	std::string _answer;

};
