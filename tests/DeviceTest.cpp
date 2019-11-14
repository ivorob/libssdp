#include <gtest/gtest.h>
#include "ssdp/Device.h"

TEST(Device, defaultConstructorTest)
{
    ssdp::Device device;
    ASSERT_EQ("", device.getUSN());
    ASSERT_EQ("", device.getDescription());
    ASSERT_EQ("", device.getLocation());

    ASSERT_FALSE(device.isValid());
}

TEST(Device, initConstructorTest)
{
    ssdp::Device device("usn-test", "http://192.168.1.1/test.xml", "Test Server");
    ASSERT_EQ("usn-test", device.getUSN());
    ASSERT_EQ("http://192.168.1.1/test.xml", device.getLocation());
    ASSERT_EQ("Test Server", device.getDescription());

    ASSERT_TRUE(device.isValid());

    ssdp::Device device1("usn-test", "http://192.168.1.1/test.xml", "");
    ASSERT_FALSE(device1.isValid());

    ssdp::Device device2("usn-test", "", "Test Server");
    ASSERT_FALSE(device2.isValid());

    ssdp::Device device3("", "http://192.168.1.1/test.xml", "Test Server");
    ASSERT_FALSE(device3.isValid());
}

TEST(Device, rawResponseTest)
{
    ssdp::Device device;
    std::string rawResponse = device.getRawResponse();
    ASSERT_TRUE(rawResponse.empty());

    device.setRawResponse("HTTP/1.1 200 OK\r\n");
    ASSERT_EQ("HTTP/1.1 200 OK\r\n", device.getRawResponse());
}
