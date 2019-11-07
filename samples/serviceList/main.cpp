#include <iostream>
#include "ssdp.h"

int
main()
{
    ssdp::Devices devices = ssdp::serviceList();
    for (const auto& device : devices) {
        std::cout << "==========================================================" << std::endl;
        std::cout << "Server\t: " << device.getDescription() << std::endl;
        std::cout << "USN\t: " << device.getUSN() << std::endl;
        std::cout << "Location: " << device.getLocation() << std::endl;
        std::cout << "==========================================================" << std::endl;
    }

    return 0;
}
