#include <iostream>
#include "ssdp/StringUtils.h"

std::string
StringUtils::trim(const std::string& data)
{
    if (data.empty()) {
        return data;
    }

    size_t position = 0;
    while (position < data.size() && isspace(data[position])) {
        ++position;
    }

    size_t rposition = data.size() - 1;
    while (rposition > position && isspace(data[rposition])) {
        --rposition;
    }

    return data.substr(position, rposition - position + 1);
}
