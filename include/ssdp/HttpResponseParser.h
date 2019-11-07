#pragma once

#include <string>
#include <sstream>
#include <map>

#include "ssdp/Device.h"

namespace ssdp {
namespace HttpResponse {

Device parse(const std::string& response);

}
}
