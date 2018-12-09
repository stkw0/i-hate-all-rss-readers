#include <QString>

#include "feed.hpp"

QFeed::QFeed(std::string url) : Feed(url) {
    setText(QString::fromStdString(_url));
}