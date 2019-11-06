#include <gtest/gtest.h>
#include "ssdp/HttpResponseParser.h"

TEST(HttpResponseParser, wrongResponseTest)
{
    ssdp::HttpResponseParser parser;
    ASSERT_FALSE(parser.parse(""));
    ASSERT_FALSE(parser.parse("TEST: wrong header"));
    ASSERT_FALSE(parser.parse("HTTP/1.0 skldf"));

    std::string response = "HTTP/1.1 200 OK\r\n"
        "CACHE-CONTROL: max-age=120\r\n"
        "ST: upnp:rootdevice\r\n"
        "EXT:\r\n"
        "SERVER: ZyXEL Communications Corp. UPnP/1.1 MiniUPnPd/1.8\r\n"
        "OPT: \"http://schemas.upnp.org/upnp/1/0/\"; ns=01\r\n"
        "01-NLS: 1\r\n"
        "BOOTID.UPNP.ORG: 1\r\n"
        "CONFIGID.UPNP.ORG: 1337\r\n";
    ASSERT_FALSE(parser.parse(response));
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

    ssdp::HttpResponseParser parser;
    ASSERT_TRUE(parser.parse(response));
    ASSERT_EQ("uuid:e1a935d8-c665-3699-3fbd-a3ecbb123855::upnp:rootdevice", parser.getUSN());
    ASSERT_EQ("http://192.168.1.1:49479/rootDesc.xml", parser.getLocation());
    ASSERT_EQ("ZyXEL Communications Corp. UPnP/1.1 MiniUPnPd/1.8", parser.getServer());

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

    ASSERT_TRUE(parser.parse(response));
    ASSERT_EQ("uuid:e1a935d8-c665-3699-3fbd-a3ecbb123855::upnp:rootdevice", parser.getUSN());
    ASSERT_EQ("http://192.168.1.1:49479/rootDesc.xml", parser.getLocation());
    ASSERT_EQ("ZyXEL Communications Corp. UPnP/1.1 MiniUPnPd/1.8", parser.getServer());

    response = "HTTP/1.1 200 OK\r\n"
               "CACHE-CONTROL: max-age=120\r\n";
    ASSERT_FALSE(parser.parse(response));
    ASSERT_EQ("", parser.getUSN());
    ASSERT_EQ("", parser.getLocation());
    ASSERT_EQ("", parser.getServer());
}
