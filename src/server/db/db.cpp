#include <iostream>

#include "db.hpp"

DB::DB(const std::string db_file) : _db{db_file} {
    _db << "create table if not exists users (\
        id bigint(20) DEFAULT NULL,\
        username varchar(255) DEFAULT NULL,\
        password varchar(255) DEFAULT NULL,\
        email varchar(255) DEFAULT NULL\
        )";

    _db << "create table if not exists feeds (\
        id bigint(20) DEFAULT NULL,\
        username varchar(255) DEFAULT NULL,\
        url varchar(255) DEFAULT NULL,\
        readed bit DEFAULT NULL \
        )";

    _db << "create table if not exists items (\
        id bigint(20) DEFAULT NULL,\
        username varchar(255) DEFAULT NULL,\
        feed varchar(255) DEFAULT NULL,\
        url varchar(255) DEFAULT NULL,\
        readed bit DEFAULT NULL \
        )";
}

void DB::registerUser(const std::string& user, const std::string& password,
                      const std::string& email) {
    _db << "INSERT INTO users (id, username, password, email) \
        VALUES (0, \'" +
               user + "\', \'" + password + "\', \'" + email + "\')";
}

std::string DB::getUserPassword(const std::string& user) {
    std::string pass;

    _db << "select password from users where username == ? ;" << user >> pass;
    return pass;
}

void DB::addFeed(const std::string& user, const std::string& feed) {
    _db << "INSERT INTO feeds (id, username, url) \
        VALUES (0, \'" +
               user + "\', \'" + feed + "\')";
}

void DB::deleteFeed(const std::string& user, const std::string& feed) {
    _db << "DELETE FROM feeds WHERE username == ? AND url == ? ;" << user << feed;
}

std::vector<std::string> DB::getFeeds(const std::string& user) {
    std::vector<std::string> feeds;
    _db << "select url from feeds where username == ? ;" << user >>
        [&](std::string url) { feeds.emplace_back(url); };

    return feeds;
}

void DB::addItem(const std::string& user, const std::string& feed, const std::string& item) {
    _db << "INSERT INTO items (id, username, feed, url) \
        VALUES (0, \'" +
               user + "\', \'" + feed + "\', \'" + item + "\')";
}

std::vector<std::string> DB::getItems(const std::string& user, const std::string& feed) {
    std::vector<std::string> items;
    _db << "select url from items where username == ? AND feed == ? ;" << user << feed >>
        [&](std::string url) { items.emplace_back(url); };

    return items;
}
