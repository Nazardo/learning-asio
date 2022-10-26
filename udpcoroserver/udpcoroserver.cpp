#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <asio.hpp>

using asio::ip::tcp;
using asio::ip::udp;

asio::awaitable<void> udplistener(asio::ip::port_type udp_port, asio::ip::port_type tcp_port) {
	auto executor = co_await asio::this_coro::executor;

	std::array<char, 1024> recv_buffer;
	std::array<char, 5> send_data = { 0xff, 0xff, 0xff, 0xff, 1 };
	std::array<unsigned char, 4> any = { 0, 0, 0, 0 };
	udp::socket socket(executor);
	asio::error_code ec;
	socket.open(udp::v4(), ec);
	std::cout << "open: " << ec << std::endl;
	socket.bind(udp::endpoint(asio::ip::address_v4::any(/*(0xC0A864FA/*0xFA64A8C0*/), udp_port), ec);
	std::cout << "bind: " << ec << std::endl;

	for (;;) {
		udp::endpoint remote_endpoint;
		std::size_t n = co_await socket.async_receive_from(asio::buffer(recv_buffer), remote_endpoint, asio::use_awaitable);
		std::cout << "Received " << n << " octets from " << remote_endpoint.address() << std::endl;
		tcp::socket client(executor);
		co_await client.async_connect(tcp::endpoint(remote_endpoint.address(), tcp_port), asio::use_awaitable);
		co_await client.async_send(asio::buffer(send_data), asio::use_awaitable);
		std::cout << "Sent sequence to " << remote_endpoint.address() << std::endl;
	}
}

int main(int argc, char** argv) {
	try
	{
		asio::io_context io_context;

		asio::signal_set signals(io_context, SIGINT, SIGTERM);
		signals.async_wait([&](auto, auto) { io_context.stop(); });

		asio::co_spawn(io_context, udplistener(30000, 30001), asio::detached);

		io_context.run();

		std::cout << "Server closed gracefully" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}