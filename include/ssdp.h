#pragma once

#include <list>
#include "ssdp/Device.h"

namespace ssdp {

typedef std::list<Device> Devices;

Devices serviceList(long int usec = 2000000) noexcept;

}
