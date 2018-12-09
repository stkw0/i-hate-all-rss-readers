#pragma once

#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "lib/package/package.hpp"
#include "db/db.hpp"
#include "lib/logging.hpp"
#include "lib/env.hpp"
#include "config.hpp"

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

	Config _cfg{"iharr"};
	DB _db{_cfg.getDBPath()};

	spdlogger _log{NewLogger("executer")};

	const std::string _secret{iharr::getenv("IHARR_SECRET")};

};