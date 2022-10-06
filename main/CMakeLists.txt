cmake_minimum_required(VERSION 3.15)
project(main)

if (MSVC)
  add_definitions(/bigobj)
endif()

set(SOURCES
    "src/main.cpp"
)

add_executable(main ${SOURCES})
set_property(TARGET main PROPERTY CXX_STANDARD 20)
target_link_libraries(main asio::asio)
target_include_directories(main PRIVATE include)
