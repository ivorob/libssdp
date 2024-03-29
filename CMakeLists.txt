CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (ssdp)

SET (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET (SOURCES
        ${SRC_DIR}/ssdp.cpp
        ${SRC_DIR}/HttpResponseParser.cpp
        ${SRC_DIR}/StringUtils.cpp
        ${SRC_DIR}/Device.cpp
        ${SRC_DIR}/AbstractSocket.cpp
        ${SRC_DIR}/UDPSocket.cpp
    )

SET (CMAKE_CXX_STANDARD 17)
SET (CMAKE_CXX_STANDARD_REQUIRED ON)

ENABLE_TESTING()

ADD_SUBDIRECTORY (${CMAKE_CURRENT_SOURCE_DIR}/third-party)
ADD_SUBDIRECTORY (${CMAKE_CURRENT_SOURCE_DIR}/tests)
ADD_SUBDIRECTORY (${CMAKE_CURRENT_SOURCE_DIR}/samples)

ADD_LIBRARY (ssdp ${SOURCES})
TARGET_INCLUDE_DIRECTORIES (ssdp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
