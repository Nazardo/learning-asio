#include <iostream>

#include <asio.hpp>

void timer_elapsed(
	const asio::error_code& /*e*/,
	asio::steady_timer* t,
	int* count)
{
	if (*count < 5)
	{
		std::cout << *count << std::endl;
		++(*count);
		t->expires_at(t->expiry() + asio::chrono::seconds(1));
		t->async_wait(std::bind(timer_elapsed, std::placeholders::_1, t, count));
	}
}

int main(int argc, char** argv) {
	std::cout << "Learning Asio " << APP_VERSION << std::endl;

	asio::io_context io;

	int count = 0;
	asio::steady_timer t(io, asio::chrono::seconds(1));
	t.async_wait(std::bind(timer_elapsed, std::placeholders::_1, &t, &count));

	io.run();
	std::cout << "Final count is " << count << std::endl;
	return 0;
}
