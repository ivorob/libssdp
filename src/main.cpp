#include <iostream>
#include <vector>

#ifdef __APPLE_CC__
#include <sys/socket.h>
#include <netdb.h>
#include <sys/time.h>
#include <arpa/inet.h>
#endif

const std::string discoveryMessage = 
    "M-SEARCH * HTTP/1.1\r\n"
    "HOST:239.255.255.250:1900\r\n"
    "ST:upnp:rootdevice\r\n"
    "MX:2\r\n"
    "MAN:\"ssdp:discover\"\r\n"
    "\r\n";

int
main()
{
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        std::cerr << "Cannot create socket" << std::endl;
        return -1;
    }

    struct timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        perror("Error");
    }

    struct sockaddr_in destAddr = {0};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(1900);
    destAddr.sin_addr.s_addr = inet_addr("239.255.255.250");
    int result = sendto(sock, reinterpret_cast<const void *>(discoveryMessage.c_str()), discoveryMessage.size(), 0,
            reinterpret_cast<const struct sockaddr *>(&destAddr), sizeof(destAddr));
    if (result < 0) {
        perror("Error");
    }

    std::vector<char> buffer(10240);
    while (result > 0) {
        struct sockaddr_in addr = {0};
        socklen_t length = sizeof(addr);
        result = recvfrom(sock, reinterpret_cast<void *>(&buffer[0]), buffer.size(), 0, 
                reinterpret_cast<struct sockaddr *>(&addr), &length);
        if (result > 0) {
            std::string answer(&buffer[0], result);
            std::cout << answer << std::endl;
        }
    }

    return 0;
}
