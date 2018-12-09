#pragma once

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "logging.hpp"


using json = nlohmann::json;

class Item {
public:
	Item(std::string url);
private:
};

class Feed {
public:
	Feed(std::string url);
	virtual ~Feed() =default;

	json& content() ;

	void addItem(const std::string& url);
	std::vector<Item> getItems();

protected:
	std::string _url;

private:
	json _content;
	std::vector<Item> _items;

	spdlogger _log{NewLogger("feed")};

};