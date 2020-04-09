#include <gtest/gtest.h>

#ifdef __APPLE_CC__
#include <sys/socket.h>
#include <arpa/inet.h>
#elif defined(WIN32)
#include <winsock2.h>
#endif 

#include "ssdp/UDPSocket.h"

TEST(SocketTest, createDestroyTest)
{
    int sockfd = -1;

    struct sockaddr_in destAddr = {0};
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(8000);
    destAddr.sin_addr.s_addr = inet_addr("239.255.255.250");

    {
        ssdp::UDPSocket socket;
        sockfd = socket.getNative();
        int result = sendto(sockfd, reinterpret_cast<const char *>("test"), 4, 0,
                reinterpret_cast<const struct sockaddr *>(&destAddr), sizeof(destAddr));
        ASSERT_TRUE(result > 0);

        result = sendto(sockfd, reinterpret_cast<const char *>("test"), 4, 0,
                reinterpret_cast<const struct sockaddr *>(&destAddr), sizeof(destAddr));
        ASSERT_TRUE(result > 0);
    }

    int result = sendto(sockfd, reinterpret_cast<const char *>("test"), 4, 0,
            reinterpret_cast<const struct sockaddr *>(&destAddr), sizeof(destAddr));
    ASSERT_FALSE(result > 0);
}
