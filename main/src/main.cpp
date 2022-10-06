#include <iostream>

#include <asio.hpp>

int main(int argc, char** argv) {
    std::cout << "Learning Asio " << APP_VERSION << std::endl;

    asio::io_context io;

    // Create a timer to expire 5 seconds from now
    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.wait(); // blocking wait on the timer

    return 0;
}
