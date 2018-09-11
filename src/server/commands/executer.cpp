#include <exception>
#include <iostream>

#include <jwt/jwt_all.h>
#include <nlohmann/json.hpp>

#include "env.hpp"
#include "executer.hpp"

using json = nlohmann::json;

std::string Executer::interpretPacket(const std::string& packet) {
    if(packet == "") return packet;

    _log->debug("Received packet: \"{}\"", packet);

    auto p = Package(packet);
    auto cmd = p.command();
    auto args = p.args();
    auto ans = dispatchCommand(cmd, args);

    json j;
    j["error"] = ans.error;
    j["answer"] = ans.answer;
    j["args"] = ans.args;
    return j.dump();
}

// Private methods

CommandResult Executer::dispatchCommand(const std::string& cmd, args_t& args) {
    std::cout << cmd << std::endl;
    if(cmd == "login") {
        return cmd_login(args);
    } else if(cmd == "register") {
        return cmd_register(args);
    } else if(cmd == "add_feed") {
        return cmd_add_feed(args);
    } else if(cmd == "get_feeds") {
        return cmd_get_feeds(args);
    }

    return CommandResult{"Invalid command", ""};
}

CommandResult Executer::cmd_login(args_t& args) try {
    std::string username = args["username"];
    std::string password = args["password"];

    HS256Validator signer(iharr::getenv("IHARR_SECRET"));
    json payload = {{"user", username}};
    auto token = JWT::Encode(signer, payload);

    args_t args;
    args["token"] = token;

    auto db_password = _db.getUserPassword(username);

    return CommandResult{"", "Correctly loged", args};
} catch(std::exception& e) {
    return CommandResult{"Error while login: " + std::string(e.what()), ""};
}

CommandResult Executer::cmd_register(args_t& args) try {
    std::string username = args["username"];
    std::string password = args["password"];
    std::string email = args["email"];

    try {
        if(_db.getUserPassword(username) != "")
            return CommandResult{"Error, user already registered", ""};
    } catch(...) {
    }

    _db.registerUser(username, password, email);
    return CommandResult{"", "User registered correctly"};
} catch(std::exception& e) {
    return CommandResult{"Error occurred while registering: " + std::string(e.what()), ""};
}

CommandResult Executer::cmd_add_feed(args_t& args) try {
    auto url = args["url"];
    auto token = args["token"];

    HS256Validator signer(iharr::getenv("IHARR_SECRET"));

    json header, payload;
    std::tie(header, payload) = JWT::Decode(token, &signer);
    std::cout << "Header: " << header << std::endl;
    std::cout << "Payload: " << payload << std::endl;

    _db.addFeed(payload["user"], url);

    return CommandResult{"", "Feed added"};
} catch(std::exception& e) {
    return CommandResult{"Error occured while adding the feed", ""};
}

CommandResult Executer::cmd_get_feeds(args_t& args) try {
    _db.getFeeds(args["username"]);

    return CommandResult{"", "OK"};
} catch(std::exception& e) {
    return CommandResult{"Error occured while getting feeds", ""};
}