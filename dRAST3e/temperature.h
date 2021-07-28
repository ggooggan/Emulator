#pragma once
#include "tcp.h"
#include "Singleton.h"
#include "TCP_subject.h"

class unit_temperature : public Singleton<unit_temperature>, public Observer<TCPSubject>
{
public:
	void thread_connect(int port)
	{
		TCPSubject::getInstance().attach(*this);

		port_ = port;
		auto th_connect = std::thread([&]() {

			boost::asio::io_context io_context;
			sv = new server(io_context, port_, "temperature");
			io_context.run();

			});

		th_connect.detach();
	}

	virtual void update(TCPSubject* subject)
	{
		std::string message = subject->getMessage();
		int rx_message = message.find("rx");
		int moduel_message = message.find("temperature");

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
		sv->sendMsg(getmsg.c_str());
	}
private:
	server* sv = nullptr;
	int port_ = 0;
};