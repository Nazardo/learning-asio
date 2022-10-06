cmake_minimum_required(VERSION 3.15)
project(tcpserver)

add_executable(tcpserver "tcpserver.cpp")
set_property(TARGET tcpserver PROPERTY CXX_STANDARD 20)
target_link_libraries(tcpserver asio::asio)
