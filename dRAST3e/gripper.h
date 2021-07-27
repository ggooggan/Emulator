#pragma once

#include "tcp.h"
#include "Singleton.h"

class unit_gripper : public Singleton< unit_gripper>
{
public:

	void thread_connect(int port)
	{
		gripper_port = port;
		auto adp_th = std::thread([&]() {

			boost::asio::io_context io_context;
			sv = new server(io_context, gripper_port, "gripper");
			io_context.run();

			});

		adp_th.detach();
	}
private:
	server* sv = nullptr;
	int gripper_port = 0;
};