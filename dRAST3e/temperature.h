#pragma once
#include "tcp.h"
#include "Singleton.h"
#include "TCP_subject.h"

class temperature_command : public Singleton<temperature_command>
{
public:
	void setValue(std::string cmd)
	{
		getValue = cmd;
	}

	std::string check_Command(const std::string cmd)
	{
		std::string result = "";
		// rtemp  100
		if (cmd == "RTEMP 100")
		{
			result = "RTEMP 100," + getValue;
		}
		else
		{
			result = cmd;
		}

		result += ",1";
		return result;
	}

private:
	std::string getValue = "0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2"; // default
};

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
		
		getmsg = temperature_command::getInstance().check_Command(getmsg);

		sv->sendMsg(getmsg.c_str());
	}
private:
	server* sv = nullptr;
	int port_ = 0;
};

