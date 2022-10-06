#include <iostream>

#include <asio.hpp>

class printer {
public:
	printer(asio::io_context& io)
		: timer(io, asio::chrono::seconds(1)),
		count(0) {
		timer.async_wait(std::bind(&printer::print, this));
	}
	~printer() {
		std::cout << "Final count is " << count << std::endl;
	}

	void print() {
		if (count < 5)
		{
			std::cout << count << std::endl;
			++count;
			timer.expires_at(timer.expiry() + asio::chrono::seconds(1));
			timer.async_wait(std::bind(&printer::print, this));
		}
	}

private:
	asio::steady_timer timer;
	int count;
};

int main(int argc, char** argv) {
	std::cout << "Learning Asio " << APP_VERSION << std::endl;

	asio::io_context io;
	printer p(io);
	io.run();

	return 0;
}
