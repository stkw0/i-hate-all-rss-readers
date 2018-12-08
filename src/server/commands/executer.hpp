#pragma once

#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "package/package.hpp"
#include "db/db.hpp"
#include "logging.hpp"
#include "env.hpp"

using json = nlohmann::json;


struct CommandResult {
	std::string error;
	std::string answer;
	json args;
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
	CommandResult cmd_delete_feed(args_t& args);
	CommandResult cmd_get_feeds(args_t& args);

	DB _db{"/tmp/lol"};

	spdlogger _log{NewLogger("executer")};

	const std::string _secret{iharr::getenv("IHARR_SECRET")};

};