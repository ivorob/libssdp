#ifdef __APPLE_CC__
#include <sys/socket.h>
#include <arpa/inet.h>
#elif defined(WIN32)
#include <winsock.h>
#endif 

#include "ssdp/UDPSocket.h"

ssdp::UDPSocket::UDPSocket()
{
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}
