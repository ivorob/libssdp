#pragma once

#include <list>
#include "ssdp/Device.h"

namespace ssdp {

typedef std::list<Device> Devices;

//serviceType can accept the following values:
//  * upnp:rootdevice
//  * ssdp:all
//  * concrete name
Devices serviceList(long int usec = 2000000, const std::string& serviceType = "upnp:rootdevice") noexcept;

}
