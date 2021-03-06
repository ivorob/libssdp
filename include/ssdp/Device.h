#pragma once

#include <string>

namespace ssdp {

class Device {
public:
    Device();
    Device(const std::string& usn, const std::string& location, const std::string& description);

    const std::string& getUSN() const;
    const std::string& getLocation() const;
    const std::string& getDescription() const;
    const std::string& getRawResponse() const;

    void setRawResponse(const std::string& response);

    bool isValid() const;
private:
    std::string usn, location, server;
    std::string rawResponse;
};

}
