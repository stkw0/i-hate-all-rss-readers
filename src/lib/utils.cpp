#include <regex>
#include <sstream>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>

#include "utils.hpp"

bool IsValidURL(const std::string& url) {
    std::regex r("(?:http|https)://([\\S]+[^<>]*)");
    return std::regex_match(url, r);
}

json GetPArsedFeed(const std::string& url) {
    Poco::URI uri("https://feed2json.org/convert?url=" + url);
    std::string path = uri.getPathAndQuery();
    if(path.empty()) path = "/";
    Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, path);
    Poco::Net::HTTPResponse response;

    session.sendRequest(request);

    std::cout << response.getStatus() << " " << response.getReason() << std::endl;
    std::istream& s = session.receiveResponse(response);

    // response.write(std::cout);
    std::stringstream s2;
    Poco::StreamCopier::copyStream(s, s2);
    // std::cout << s2.str();
    return json::parse(s2.str());
}