cmake_minimum_required(VERSION 3.15)
project(udpcoroserver)

add_executable(udpcoroserver "udpcoroserver.cpp")
set_property(TARGET udpcoroserver PROPERTY CXX_STANDARD 20)
target_link_libraries(udpcoroserver asio::asio)
