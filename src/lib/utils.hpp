#pragma once

#include <regex>
#include <string>

bool IsValidURL(const std::string& url) {
    std::regex r("(?:http|https)://([\\S]+[^<>]*)");
    return std::regex_match(url, r);
}