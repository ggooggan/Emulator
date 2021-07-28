#pragma once
#include "tcp.h"
#include "Singleton.h"
#include "TCP_subject.h"

class unit_gripper : public Singleton<unit_gripper>, public Observer<TCPSubject>
{
public:
	void thread_connect(int port)
	{
		TCPSubject::getInstance().attach(*this);
		port_ = port;
		auto th_connect = std::thread([&]() {

			boost::asio::io_context io_context;
			sv = new server(io_context, port_, "gripper");
			io_context.run();

			});

		th_connect.detach();
		
	}

	virtual void update(TCPSubject* subject)
	{
		std::string message = subject->getMessage();
		int rx_message = message.find("rx");
		int moduel_message = message.find("gripper");

		if (rx_message != -1 && moduel_message != -1)
			checkMsg(message);
	}

	void checkMsg(std::string& msg)
	{
		// message check;
		std::string getmsg = msg;
		int aa = msg.find("]") + 2;
		getmsg = msg.substr(aa);
		getmsg += ",1";
		const char* c = getmsg.c_str();
		sv->sendMsg(c);
	}
private:
	server* sv = nullptr;
	int port_ = 0;
};