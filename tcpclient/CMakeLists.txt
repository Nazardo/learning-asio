cmake_minimum_required(VERSION 3.15)
project(tcpclient)

add_executable(tcpclient "tcpclient.cpp")
set_property(TARGET tcpclient PROPERTY CXX_STANDARD 20)
target_link_libraries(tcpclient asio::asio)
