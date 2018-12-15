#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>

#include <jwt/jwt_all.h>

#include "executer.hpp"
#include "lib/utils.hpp"

#define BIND(CLASS_NAME, CMD_NAME, args)                                       \
    { #CMD_NAME, std::bind(&CLASS_NAME::cmd_##CMD_NAME, this, args) }

#define COMMAND(F) BIND(Executer, F, args)

using command_map_t =
    std::unordered_map<std::string, std::function<CommandResult(args_t&)>>;

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

    command_map_t m = {
        COMMAND(login),       COMMAND(register),  COMMAND(add_feed),
        COMMAND(delete_feed), COMMAND(get_feeds), COMMAND(add_item),
        COMMAND(get_items),
    };

    if(const auto func = m.find(cmd); func != m.end()) {
        return func->second(args);
    } else {
        return CommandResult{"Invalid command", ""};
    }
}

CommandResult Executer::cmd_login(args_t& args) try {
    auto username = args["username"];
    auto password = args["password"];

    HS256Validator signer(_secret);
    json payload = {{"user", username}};
    auto token = JWT::Encode(signer, payload);

    args_t ret_args;
    ret_args["token"] = token;

    auto db_password = _db.getUserPassword(username);

    if(db_password != password) throw std::runtime_error("Incorrect");

    return CommandResult{"", "Correctly loged", ret_args};
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

    HS256Validator signer(_secret);
    auto [header, payload] = JWT::Decode(token, &signer);

    if(!IsValidURL(url)) throw std::runtime_error("Invalid URL");

    auto feeds = _db.getFeeds(payload["user"]);
    for(auto&& f : feeds)
        if(f == url) throw std::runtime_error("Feed already present");

    GetParsedFeed(url);

    _db.addFeed(payload["user"], url);

    return CommandResult{"", "Feed added"};
} catch(std::exception& e) {
    return CommandResult{"Error occured while adding the feed", ""};
}

CommandResult Executer::cmd_delete_feed(args_t& args) try {
    auto url = args["url"];
    auto token = args["token"];

    HS256Validator signer(_secret);
    auto [header, payload] = JWT::Decode(token, &signer);

    _db.deleteFeed(payload["user"], url);

    return CommandResult{"", "Feed removed"};
} catch(std::exception& e) {
    return CommandResult{"Error occured while deleting feed", ""};
}

CommandResult Executer::cmd_get_feeds(args_t& args) try {
    auto token = args["token"];

    HS256Validator signer(_secret);
    auto [header, payload] = JWT::Decode(token, &signer);

    auto feeds = _db.getFeeds(payload["user"]);

    return CommandResult{"", "OK", feeds};
} catch(std::exception& e) {
    return CommandResult{"Error occured while getting feeds", ""};
}

CommandResult Executer::cmd_add_item(args_t& args) try {
    auto feed = args["feed"];
    auto url = args["url"];
    auto token = args["token"];

    HS256Validator signer(_secret);
    auto [header, payload] = JWT::Decode(token, &signer);

    if(!IsValidURL(url)) throw std::runtime_error("Invalid URL");

    auto items = _db.getItems(payload["user"], feed);
    for(auto&& i : items)
        if(i == url) throw std::runtime_error("Feed already present");

    _db.addItem(payload["user"], feed, url);

    return CommandResult{"", "Item added"};
} catch(std::exception& e) {
    return CommandResult{"Error occured while adding item" + std::string(e.what()), ""};
}

CommandResult Executer::cmd_get_items(args_t& args) try {
    auto token = args["token"];
    auto feed = args["feed"];

    HS256Validator signer(_secret);
    auto [header, payload] = JWT::Decode(token, &signer);

    auto items = _db.getItems(payload["user"], feed);
    return CommandResult{"", "OK", items};
} catch(std::exception& e) {
    return CommandResult{"Error occured while getting items", ""};
}
