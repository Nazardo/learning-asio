#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;

int main(int argc, char** argv) {
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: tcpclient <host>" << std::endl;
			return 1;
		}
		asio::io_context io_context;
		tcp::resolver resolver(io_context);
		// A resolver takes a host name and service name
		// and turns them into a list of endpoints
		tcp::resolver::results_type endpoints =
			resolver.resolve(argv[1], "daytime");

		tcp::socket socket(io_context);
		// asio::connect() automatically goes through all
		// endpoints until one works.
		asio::connect(socket, endpoints);
		// Here the connection is open.

		for (;;)
		{
			std::array<char, 128> buf;
			asio::error_code error;

			size_t len = socket.read_some(asio::buffer(buf), error);

			if (error == asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw asio::system_error(error); // Some other error.

			std::cout.write(buf.data(), len);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}