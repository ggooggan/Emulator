#pragma once
#include "tcp.h"
#include "Singleton.h"
#include "TCP_subject.h"

class stage_command : public Singleton<stage_command>
{
public:

	std::string check_Command(const std::string cmd)
	{
		std::string result = "";

		if (cmd == "MPS OPTIC")
		{
			result = "MPS OPTIC 0,0,0,0";
		}
		else
		{
			result = cmd;
		}


		result += ",1";
		return result;
	}

};

class unit_stage : public Singleton<unit_stage>, public Observer<TCPSubject>
{
public:
	void thread_connect(int port)
	{
		TCPSubject::getInstance().attach(*this);
		port_ = port;
		auto th_connect = std::thread([&]() {

			boost::asio::io_context io_context;
			sv = new server(io_context, port_, "stage");
			io_context.run();

			});

		th_connect.detach();
	}

	virtual void update(TCPSubject* subject)
	{
		std::string message = subject->getMessage();
		int rx_message = message.find("rx");
		int moduel_message = message.find("stage");

		if (rx_message != -1 && moduel_message != -1)
			checkMsg(message);
	}

	void checkMsg(std::string& msg)
	{
		// message check;
		std::string getmsg = msg;
		int aa = msg.find("]") + 2;
		getmsg = msg.substr(aa);

		getmsg = stage_command::getInstance().check_Command(getmsg);

		if (getmsg.length() > 0)
			sv->sendMsg(getmsg.c_str());
	}

	void tcp_delay(int second)
	{
		sv->delay_TCP(second);
	}

private:
	server* sv = nullptr;
	int port_ = 0;
};