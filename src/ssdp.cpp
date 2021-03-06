#include <vector>

#ifdef __APPLE_CC__
#include <netdb.h>
#include <sys/time.h>
#include <arpa/inet.h>
#elif defined(WIN32)
#include <ws2tcpip.h>
#include <windows.h>
#endif

#include "ssdp.h"
#include "ssdp/HttpResponseParser.h"
#include "ssdp/UDPSocket.h"
#include "ssdp/StringUtils.h"

const std::string discoveryMessage = 
    "M-SEARCH * HTTP/1.1\r\n"
    "HOST:239.255.255.250:1900\r\n"
    "ST:upnp:rootdevice\r\n"
    "MX:2\r\n"
    "MAN:\"ssdp:discover\"\r\n"
    "\r\n";

ssdp::Devices
ssdp::serviceList(long int usec) noexcept
{
    Devices devices;

    UDPSocket socket;
    if (socket.getNative() < 0) {
        return devices;
    }

    struct timeval tv = {0};
    if ((usec / 1000000) > 0) {
        tv.tv_sec = usec / 1000000;
    } else {
        tv.tv_sec = 0;
    }
    tv.tv_usec = usec % 1000000;
    if (setsockopt(socket.getNative(), SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char *>(&tv), sizeof(tv)) < 0) {
        return devices;
    }

    struct sockaddr_in destAddr = {0};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(1900);
    inet_pton(AF_INET, "239.255.255.250", &destAddr.sin_addr.s_addr);
    int result = sendto(socket.getNative(), reinterpret_cast<const char *>(discoveryMessage.c_str()), static_cast<int>(discoveryMessage.size()), 0,
            reinterpret_cast<const struct sockaddr *>(&destAddr), sizeof(destAddr));
    if (result < 0) {
        return devices;
    }

    std::vector<char> buffer(10240);
    while (result > 0) {
        struct sockaddr_in addr = {0};
        socklen_t length = sizeof(addr);
        result = recvfrom(socket.getNative(), reinterpret_cast<char *>(&buffer[0]), static_cast<int>(buffer.size()), 0, 
                reinterpret_cast<struct sockaddr *>(&addr), &length);
        if (result > 0) {
            std::string answer(&buffer[0], result);

            try {
                Device device = HttpResponse::parse(answer);
                if (device.isValid()) {
                    device.setRawResponse(StringUtils::trim(answer));
                    devices.push_back(device);
                }
            } catch (const std::invalid_argument&) {
            }
        }
    }

    return devices;
}
