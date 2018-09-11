#pragma once

#include <string>
#include <unordered_map>

#include "package/package.hpp"
#include "db/db.hpp"
#include "logging.hpp"

struct CommandResult {
	std::string error;
	std::string answer;
	args_t args;
};

	using args_t = std::unordered_map<std::string, std::string>;

class Executer {
public:
	std::string interpretPacket(const std::string& packet);
private:
	CommandResult dispatchCommand(const std::string& cmd, args_t& args);

	CommandResult cmd_login(args_t& args);
	CommandResult cmd_register(args_t& args);
	CommandResult cmd_add_feed(args_t& args);
	CommandResult cmd_get_feeds(args_t& args);

	DB _db{"/tmp/lol"};

	spdlogger _log{NewLogger("executer")};

};