#include <iostream>
#include "ssdp.h"

#if defined(WIN32)
#include <winsock2.h>
#endif

int
main()
{
#if defined(WIN32)
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    ssdp::Devices devices = ssdp::serviceList();
    for (const auto& device : devices) {
        std::cout << "==================================================" << std::endl;
        std::cout << device.getRawResponse() << std::endl;
        std::cout << "==================================================" << std::endl;
    }

#if defined(WIN32)
    WSACleanup();
#endif

    return 0;
}
