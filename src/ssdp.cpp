#include <vector>

#ifdef __APPLE_CC__
#include <netdb.h>
#include <sys/time.h>
#include <arpa/inet.h>
#endif

#include "ssdp.h"
#include "ssdp/HttpResponseParser.h"
#include "ssdp/UDPSocket.h"
#include "ssdp/StringUtils.h"

ssdp::Devices
ssdp::serviceList(long int usec, const std::string& serviceType) noexcept
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
    if (setsockopt(socket.getNative(), SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        return devices;
    }

    std::string discoveryMessage = 
        "M-SEARCH * HTTP/1.1\r\n"
        "HOST:239.255.255.250:1900\r\n"
        "ST:" + serviceType +  "\r\n"
        "MX:2\r\n"
        "MAN:\"ssdp:discover\"\r\n"
        "\r\n";


    struct sockaddr_in destAddr = {0};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(1900);
    destAddr.sin_addr.s_addr = inet_addr("239.255.255.250");
    int result = sendto(socket.getNative(), reinterpret_cast<const void *>(discoveryMessage.c_str()), discoveryMessage.size(), 0,
            reinterpret_cast<const struct sockaddr *>(&destAddr), sizeof(destAddr));
    if (result < 0) {
        return devices;
    }

    std::vector<char> buffer(10240);
    while (result > 0) {
        struct sockaddr_in addr = {0};
        socklen_t length = sizeof(addr);
        result = recvfrom(socket.getNative(), reinterpret_cast<void *>(&buffer[0]), buffer.size(), 0, 
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
