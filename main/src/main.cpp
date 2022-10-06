#include <iostream>

#include <asio.hpp>

void timer_elapsed(const asio::error_code& /*e*/)
{
    std::cout << "Timer elapsed" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "Learning Asio " << APP_VERSION << std::endl;

    asio::io_context io;

    // Create a timer to expire 5 seconds from now
    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.async_wait(&timer_elapsed);

    io.run();

    return 0;
}
