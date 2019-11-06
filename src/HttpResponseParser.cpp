#include <strings.h>
#include <algorithm>

#include "ssdp/HttpResponseParser.h"
#include "ssdp/StringUtils.h"

bool 
ssdp::HttpResponseParser::parse(const std::string& response)
{
    this->headers.clear();

    std::stringstream input(response);
    bool result = parseStatusString(input);
    if (result) {
        result = parseHeaders(input);
    }

    return result;
}

bool
ssdp::HttpResponseParser::parseStatusString(std::stringstream& input) const
{
    bool result = false;

    std::string current;
    input >> current;
    if (current.size() == 8 && strncasecmp(current.c_str(), "HTTP/", 5) == 0) {
        input >> current;
        result = current == "200";
    }

    return result;
}

bool
ssdp::HttpResponseParser::parseHeaders(std::stringstream& input)
{
    std::string line;
    while (std::getline(input, line)) {
        size_t position = line.find(':');
        if (position != std::string::npos) {
            std::string headerName = StringUtils::trim(line.substr(0, position));
            std::string headerValue = StringUtils::trim(line.substr(position + 1));

            std::transform(headerName.begin(), headerName.end(), headerName.begin(), ::toupper);

            this->headers[headerName] = headerValue;
        }
    }

    return this->headers.find("USN") != this->headers.end() &&
           this->headers.find("LOCATION") != this->headers.end() &&
           this->headers.find("SERVER") != this->headers.end();
}

std::string
ssdp::HttpResponseParser::getUSN() const
{
    auto it = this->headers.find("USN");
    return it != this->headers.end() ? it->second : std::string();
}

std::string
ssdp::HttpResponseParser::getLocation() const
{
    auto it = this->headers.find("LOCATION");
    return it != this->headers.end() ? it->second : std::string();
}

std::string
ssdp::HttpResponseParser::getServer() const
{
    auto it = this->headers.find("SERVER");
    return it != this->headers.end() ? it->second : std::string();
}
