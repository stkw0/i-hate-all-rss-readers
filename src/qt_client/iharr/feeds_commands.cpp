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

    for(auto&& e : cmd.getArgsAsList()) {
        auto new_feed = new QFeed(e);
        for(auto& item : new_feed->content()["items"]) {
            addItem(e, item["url"]);
            new_feed->addItem(item["url"]);
        }

        v.emplace_back(new_feed);
    }

    return v;
}

void FeedsCommands::addItem(const std::string& feed, const std::string& url) {
    Command cmd{_c, "add_item"};
    cmd.addArg("feed", feed);
    cmd.addArg("url", url);
    cmd.addArg("token", _token);
    cmd.send();
}
