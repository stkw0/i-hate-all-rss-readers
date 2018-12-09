#include <regex>
#include <sstream>
#include <stdexcept>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>

#include "logging.hpp"
#include "utils.hpp"

bool IsValidURL(const std::string& url) {
    std::regex r("(?:http|https)://([\\S]+[^<>]*)");
    return std::regex_match(url, r);
}

json GetParsedFeed(const std::string& url) {
    auto log = NewLogger("main");

    Poco::URI uri("https://feed2json.org/convert?url=" + url);
    std::string path = uri.getPathAndQuery();
    if(path.empty()) path = "/";
    log->info("Visiting \"{}\"", path);

    Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, path);
    Poco::Net::HTTPResponse response;

    if(!session.sendRequest(request).good())
        throw std::runtime_error("Could not connect");

    // std::cout << response.getStatus() << " " << response.getReason() <<
    // std::endl;
    std::istream& s = session.receiveResponse(response);

    // response.write(std::cout);
    std::stringstream s2;
    Poco::StreamCopier::copyStream(s, s2);
    // std::cout << s2.str();
    return json::parse(s2.str());
}