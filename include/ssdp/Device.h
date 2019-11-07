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

    bool isValid() const;
private:
    std::string usn, location, server;
};

}
