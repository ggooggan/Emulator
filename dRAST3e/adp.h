#pragma once
#include "tcp.h"
#include "Singleton.h"

class unit_adp : public Singleton<unit_adp>
{
public:
	void thread_connect(int port)
	{
		adp_port = port;
		auto adp_th = std::thread([&]() {

			boost::asio::io_context io_context;
			sv = new server(io_context, adp_port, "adp");
			io_context.run();

			});

		adp_th.detach();
	}
private:
	server* sv = nullptr;
	int adp_port = 0;
};