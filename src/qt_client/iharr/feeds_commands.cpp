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

const std::vector<QListWidgetItem*> FeedsCommands::getFeeds() {
    std::vector<QListWidgetItem*> v;
    Command cmd{_c, "get_feeds"};
    cmd.addArg("token", _token);
    cmd.send();

    for(auto&& e : cmd.getArgsAsList()) v.emplace_back(new QFeed(e));

    return v;
}
