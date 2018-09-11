#pragma once

#include <string>

#include <sqlite_modern_cpp.h>

/*#include <sqlpp11/sqlite3/sqlite3.h>
#include <sqlpp11/sqlpp11.h>

namespace sql = sqlpp::sqlite3;
using namespace sqlpp;
*/

class DB {
public:
	DB(const std::string db_file = ":memory:");

	std::string getUserPassword(const std::string& user);
	void registerUser(const std::string& user, const std::string& password, const std::string& email);

	void addFeed(const std::string& user, const std::string& feed);
	void getFeeds(const std::string& user);

private:

	sqlite::database _db;
};