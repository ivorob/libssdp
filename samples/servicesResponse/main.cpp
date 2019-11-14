#include <iostream>
#include "ssdp.h"

int
main()
{
    ssdp::Devices devices = ssdp::serviceList();
    for (const auto& device : devices) {
        std::cout << "==================================================" << std::endl;
        std::cout << device.getRawResponse() << std::endl;
        std::cout << "==================================================" << std::endl;
    }

    return 0;
}
