#include <iostream>

#include <asio.hpp>

class printer {
public:
	printer(asio::io_context& io) :
		strand(asio::make_strand(io)),
		timer1(io, asio::chrono::seconds(1)),
		timer2(io, asio::chrono::seconds(1)),
		count(0) {
		timer1.async_wait(asio::bind_executor(strand, std::bind(&printer::print1, this)));
		timer2.async_wait(asio::bind_executor(strand, std::bind(&printer::print2, this)));
	}
	~printer() {
		std::cout << "Final count is " << count << std::endl;
	}

	void print1() {
		if (count < 20)
		{
			std::cout << "Timer 1: " << count << std::endl;
			++count;
			timer1.expires_at(timer1.expiry() + asio::chrono::seconds(1));
			timer1.async_wait(asio::bind_executor(strand, std::bind(&printer::print1, this)));
		}
	}

	void print2() {
		if (count < 20)
		{
			std::cout << "Timer 2: " << count << std::endl;
			++count;
			timer2.expires_at(timer2.expiry() + asio::chrono::seconds(1));
			timer2.async_wait(asio::bind_executor(strand, std::bind(&printer::print2, this)));
		}
	}

private:
	asio::strand<asio::io_context::executor_type> strand;
	asio::steady_timer timer1;
	asio::steady_timer timer2;
	int count;
};

int main(int argc, char** argv) {
	std::cout << "Learning Asio " << APP_VERSION << std::endl;

	asio::io_context io;
	printer p(io);
	// Call io.run() from two threads
	std::thread t(static_cast<asio::io_context::count_type(asio::io_context::*)()>(&asio::io_context::run), &io);
	io.run();
	t.join();

	return 0;
}
