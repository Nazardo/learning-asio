cmake_minimum_required(VERSION 3.15)
project(timer)

add_executable(timer "timer.cpp")
set_property(TARGET timer PROPERTY CXX_STANDARD 20)
target_link_libraries(timer asio::asio)
