#include "ssdp/Device.h"

ssdp::Device::Device()
{
}

ssdp::Device::Device(const std::string& usn, const std::string& location, const std::string& description)
    : usn(usn),
      location(location),
      server(description)
{
}

const std::string&
ssdp::Device::getUSN() const
{
    return this->usn;
}

const std::string&
ssdp::Device::getLocation() const
{
   return this->location;
}

const std::string&
ssdp::Device::getDescription() const
{
    return this->server;
}

bool
ssdp::Device::isValid() const
{
    return !this->usn.empty() &&
           !this->location.empty() &&
           !this->server.empty();
}
