#pragma once

#include <string>
#include <sstream>
#include <map>

namespace ssdp {

class HttpResponseParser {
public:
    bool parse(const std::string& response);

    std::string getUSN() const;
    std::string getLocation() const;
    std::string getServer() const;
private:
    bool parseStatusString(std::stringstream& input) const;
    bool parseHeaders(std::stringstream& input);
private:
    std::string usn;
    std::string location;
    std::map<std::string, std::string> headers;
};

}
