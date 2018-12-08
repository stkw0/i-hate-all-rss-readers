#pragma once

#include <string>
#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool IsValidURL(const std::string& url);

json GetPArsedFeed(const std::string& url);