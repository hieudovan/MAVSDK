cmake_minimum_required(VERSION 2.8.12)

project(mavlink_ftp_client)

find_package(Threads REQUIRED)

if(NOT MSVC)
    add_definitions("-std=c++11 -Wall -Wextra -Werror")
else()
    add_definitions("-std=c++11 -WX -W2")
endif()

find_package(MAVSDK REQUIRED)

add_executable(mavlink_ftp_client
    mavlink_ftp_client.cpp
)

target_link_libraries(mavlink_ftp_client
    MAVSDK::mavsdk_mavlink_ftp
    MAVSDK::mavsdk
    ${CMAKE_THREAD_LIBS_INIT}
)
