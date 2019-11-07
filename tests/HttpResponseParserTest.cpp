#include <gtest/gtest.h>
#include "ssdp/HttpResponseParser.h"

TEST(HttpResponseParser, wrongResponseTest)
{
    try {
        ssdp::Device device = ssdp::HttpResponse::parse("");
        FAIL() << "No exception because of invalid argument";
    } catch (const std::invalid_argument&) {
    }

    try {
        ssdp::Device device = ssdp::HttpResponse::parse("TEST: wrong header");
        FAIL() << "No exception because of invalid argument";
    } catch (const std::invalid_argument&) {
    }

    try {
        ssdp::Device device = ssdp::HttpResponse::parse("HTTP/1.0 test");
        FAIL() << "No exception because of invalid argument";
    } catch (const std::invalid_argument&) {
    }

    std::string response = "HTTP/1.1 200 OK\r\n"
        "CACHE-CONTROL: max-age=120\r\n"
        "ST: upnp:rootdevice\r\n"
        "EXT:\r\n"
        "SERVER: ZyXEL Communications Corp. UPnP/1.1 MiniUPnPd/1.8\r\n"
        "OPT: \"http://schemas.upnp.org/upnp/1/0/\"; ns=01\r\n"
        "01-NLS: 1\r\n"
        "BOOTID.UPNP.ORG: 1\r\n"
        "CONFIGID.UPNP.ORG: 1337\r\n";
    ssdp::Device device = ssdp::HttpResponse::parse(response);
    ASSERT_FALSE(device.isValid());
}

TEST(HttpResponseParser, validResponseTest)
{
    std::string response = "HTTP/1.1 200 OK\r\n"
        "CACHE-CONTROL: max-age=120\r\n"
        "ST: upnp:rootdevice\r\n"
        "USN: uuid:e1a935d8-c665-3699-3fbd-a3ecbb123855::upnp:rootdevice\r\n"
        "EXT:\r\n"
        "SERVER: ZyXEL Communications Corp. UPnP/1.1 MiniUPnPd/1.8\r\n"
        "LOCATION: http://192.168.1.1:49479/rootDesc.xml\r\n"
        "OPT: \"http://schemas.upnp.org/upnp/1/0/\"; ns=01\r\n"
        "01-NLS: 1\r\n"
        "BOOTID.UPNP.ORG: 1\r\n"
        "CONFIGID.UPNP.ORG: 1337\r\n";

    ssdp::Device device = ssdp::HttpResponse::parse(response);
    ASSERT_TRUE(device.isValid());
    ASSERT_EQ("uuid:e1a935d8-c665-3699-3fbd-a3ecbb123855::upnp:rootdevice", device.getUSN());
    ASSERT_EQ("http://192.168.1.1:49479/rootDesc.xml", device.getLocation());
    ASSERT_EQ("ZyXEL Communications Corp. UPnP/1.1 MiniUPnPd/1.8", device.getDescription());

    response = "HTTP/1.1 200 OK\r\n"
        "CACHE-CONTROL: max-age=120\r\n"
        "ST: upnp:rootdevice\r\n"
        "usn: uuid:e1a935d8-c665-3699-3fbd-a3ecbb123855::upnp:rootdevice\r\n"
        "EXT:\r\n"
        "server: ZyXEL Communications Corp. UPnP/1.1 MiniUPnPd/1.8\r\n"
        "location: http://192.168.1.1:49479/rootDesc.xml\r\n"
        "OPT: \"http://schemas.upnp.org/upnp/1/0/\"; ns=01\r\n"
        "01-NLS: 1\r\n"
        "BOOTID.UPNP.ORG: 1\r\n"
        "CONFIGID.UPNP.ORG: 1337\r\n";

    device = ssdp::HttpResponse::parse(response);
    ASSERT_TRUE(device.isValid());
    ASSERT_EQ("uuid:e1a935d8-c665-3699-3fbd-a3ecbb123855::upnp:rootdevice", device.getUSN());
    ASSERT_EQ("http://192.168.1.1:49479/rootDesc.xml", device.getLocation());
    ASSERT_EQ("ZyXEL Communications Corp. UPnP/1.1 MiniUPnPd/1.8", device.getDescription());
}
