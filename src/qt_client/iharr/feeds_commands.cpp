#include "feeds_commands.hpp"

FeedsCommands::FeedsCommands(Comm& c, const std::string& t) : _c{c}, _token{t} {
}

void FeedsCommands::addFeed(const std::string& url) {
    Command cmd{_c, "add_feed"};
    cmd.addArg("url", url);
    cmd.addArg("token", _token);
    cmd.send();
}

void FeedsCommands::deleteFeed(const std::string& url) {
    Command cmd{_c, "delete_feed"};
    cmd.addArg("url", url);
    cmd.addArg("token", _token);
    cmd.send();
}

const std::vector<std::string> FeedsCommands::getFeeds() {
    Command cmd{_c, "get_feeds"};
    cmd.addArg("token", _token);
    cmd.send();
    return cmd.getArgsAsList();
}
