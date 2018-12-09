#pragma once

#include <string>
#include <vector>

#include <sqlite_modern_cpp.h>

class DB {
public:
	DB(const std::string db_file = ":memory:");

	std::string getUserPassword(const std::string& user);
	void registerUser(const std::string& user, const std::string& password, const std::string& email);

	void addFeed(const std::string& user, const std::string& feed);
	void deleteFeed(const std::string& user, const std::string& feed);
	std::vector<std::string> getFeeds(const std::string& user);
	std::vector<std::string> getItems(const std::string& user, const std::string& feed);

private:

	sqlite::database _db;
};