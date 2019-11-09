#pragma once

namespace ssdp {

class AbstractSocket {
public:
    AbstractSocket();
    virtual ~AbstractSocket();

    int getNative() const;
protected:
    int sockfd;
};

}
