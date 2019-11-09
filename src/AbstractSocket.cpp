#ifdef __APPLE_CC__
#include <unistd.h>
#endif 

#include "ssdp/AbstractSocket.h"

ssdp::AbstractSocket::AbstractSocket()
    : sockfd(-1)
{
}

ssdp::AbstractSocket::~AbstractSocket()
{
    if (this->sockfd > 0) {
        close(this->sockfd);
    }
}

int
ssdp::AbstractSocket::getNative() const
{
    return this->sockfd;
}
