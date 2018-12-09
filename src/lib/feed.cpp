#include <exception>

#include <fmt/format.h>

#include "feed.hpp"
#include "utils.hpp"

using namespace fmt::literals;

Item::Item(std::string url) {
}

Feed::Feed(std::string url) {
    try {
        _content = GetParsedFeed(url);
        _url = "({}) {}"_format(_content["items"].size(), url);
    } catch(std::exception& e) {
        _log->error(e.what());
    }
}

json& Feed::content() {
    return _content;
}

void Feed::addItem(const std::string& url) {
    _items.emplace_back(url);
}

std::vector<Item> Feed::getItems() {
    return _items;
}