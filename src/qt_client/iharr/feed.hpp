#pragma once

#include <string>

#include <QListWidgetItem>
#include <nlohmann/json.hpp>
#include "lib/feed.hpp"

using json = nlohmann::json;

class QFeed : public QListWidgetItem, public Feed {
public:
	QFeed(std::string url);
};