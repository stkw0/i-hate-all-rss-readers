#pragma once

#include <string>
#include <vector>

#include <QListWidgetItem>

#include "comm.h"
#include "feed.hpp"

class FeedsCommands {
public:
	FeedsCommands( Comm& c, const std::string& t);

	void addFeed(const std::string& url);
	void deleteFeed(const std::string& url);
	const std::vector<QListWidgetItem*> getFeeds();

private:
	void addItem(const std::string& feed, const std::string& url);


	Comm& _c;
	const std::string& _token;

};

