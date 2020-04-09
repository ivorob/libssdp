#if __APPLE_CC__
#include <strings.h>
#elif defined(WIN32)
#include <tchar.h>
const auto& strncasecmp=_tcsnicmp;
#endif

#include <algorithm>

#include "ssdp/HttpResponseParser.h"
#include "ssdp/StringUtils.h"

namespace {

bool
parseStatusString(std::stringstream& input)
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

std::map<std::string, std::string>
parseHeaders(std::stringstream& input)
{
    std::map<std::string, std::string> headers;

    std::string line;
    while (std::getline(input, line)) {
        size_t position = line.find(':');
        if (position != std::string::npos) {
            std::string headerName = StringUtils::trim(line.substr(0, position));
            std::string headerValue = StringUtils::trim(line.substr(position + 1));

            std::transform(headerName.begin(), headerName.end(), headerName.begin(), ::toupper);

            headers[headerName] = headerValue;
        }
    }

    return headers;
}


}

ssdp::Device
ssdp::HttpResponse::parse(const std::string& response)
{
    std::stringstream input(response);
    bool result = parseStatusString(input);
    if (result) {
        const std::map<std::string, std::string>& headers = parseHeaders(input);
        if (!headers.empty()) {
            const auto& serverIt = headers.find("SERVER");
            const auto& usnIt = headers.find("USN");
            const auto& locationIt = headers.find("LOCATION");

            std::string emptyString;
            return ssdp::Device(
                    (usnIt != headers.end()) ? usnIt->second : emptyString,
                    (locationIt != headers.end()) ? locationIt->second : emptyString,
                    (serverIt != headers.end()) ? serverIt->second : emptyString);
        }
    }

    throw std::invalid_argument("Invalid HTTP response");
    return ssdp::Device();
}
