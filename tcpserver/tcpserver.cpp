#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <asio.hpp>

using asio::ip::tcp;

std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}

class tcp_connection
	: public std::enable_shared_from_this<tcp_connection>
{
public:
	typedef std::shared_ptr<tcp_connection> pointer;

	static pointer create(asio::io_context& io_context)
	{
		return pointer(new tcp_connection(io_context));
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		// The data to be sent is stored in the
		// class member `message` as we need to keep
		// the data valid until the async operation is done.
		message = make_daytime_string();

		asio::async_write(socket_, asio::buffer(message),
			std::bind(&tcp_connection::handle_write, shared_from_this(),
				std::placeholders::_1,
				std::placeholders::_2));
	}
private:
	tcp::socket socket_;
	std::string message;

	tcp_connection(asio::io_context& io_context)
		: socket_(io_context)
	{
	}

	void handle_write(const asio::error_code& /*error*/,
		size_t /*bytes_transferred*/)
	{
	}
};

class tcp_server {
public:
	tcp_server(asio::io_context& io_context, asio::ip::port_type port_num) :
		io_context(io_context),
		acceptor(io_context, tcp::endpoint(tcp::v4(), port_num))
	{
		start_accept();
	}
private:
	asio::io_context& io_context;
	tcp::acceptor acceptor;

	void start_accept() {
		tcp_connection::pointer new_connection =
			tcp_connection::create(io_context);
		acceptor.async_accept(
			new_connection->socket(),
			std::bind(&tcp_server::handle_accept, this, new_connection, std::placeholders::_1));
	}

	void handle_accept(tcp_connection::pointer new_connection,
		const asio::error_code& error)
	{
		if (!error)
		{
			new_connection->start();
		}

		start_accept();
	}
};

int main(int argc, char** argv) {
	try
	{
		asio::io_context io_context;
		tcp_server server(io_context, 13);
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}