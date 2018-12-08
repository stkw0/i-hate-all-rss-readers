#pragma once

#include <string>
#include <vector>

#include "comm.h"

class FeedsCommands {
public:
	FeedsCommands( Comm& c, const std::string& t);

	void addFeed(const std::string& url);
	void deleteFeed(const std::string& url);
	const std::vector<std::string> getFeeds();

private:
	Comm& _c;
	const std::string& _token;

};

