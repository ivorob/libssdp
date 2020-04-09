#include <gtest/gtest.h>

#if defined(WIN32)
#include <winsock2.h>
#endif

int
main(int argc, char *argv[])
{

#if defined(WIN32)
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
