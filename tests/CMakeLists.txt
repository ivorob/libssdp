CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (tests)

SET (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
SET (MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src)
SET (MAIN_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)
SET (SOURCES
        ${SRC_DIR}/tests.cpp
        ${SRC_DIR}/HttpResponseParserTest.cpp
        ${SRC_DIR}/StringUtilsTest.cpp
        ${SRC_DIR}/DeviceTest.cpp
        ${SRC_DIR}/SocketTest.cpp
        ${MAIN_SRC_DIR}/HttpResponseParser.cpp
        ${MAIN_SRC_DIR}/StringUtils.cpp
        ${MAIN_SRC_DIR}/Device.cpp
        ${MAIN_SRC_DIR}/AbstractSocket.cpp
        ${MAIN_SRC_DIR}/UDPSocket.cpp
    )

ADD_EXECUTABLE (tests ${SOURCES})
TARGET_LINK_LIBRARIES (tests gtest)
TARGET_INCLUDE_DIRECTORIES (tests PRIVATE ${MAIN_INCLUDE_DIR})

IF (WIN32)
    TARGET_LINK_LIBRARIES (tests ws2_32)
ENDIF (WIN32)

ADD_TEST(
    NAME
        gtest
    COMMAND
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests --gtest_output=xml:testresults.xml
)
