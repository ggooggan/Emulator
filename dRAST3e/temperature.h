#pragma once
#include <vector>
#include <boost/lexical_cast.hpp>
#include "tcp.h"
#include "Singleton.h"
#include "TCP_subject.h"

class temperature_command : public Singleton<temperature_command>
{
public:
	void setValue(const std::vector<std::string> get_value)
	{
		vector_value = get_value;
	}

	std::string check_Command(const std::string cmd)
	{
		std::string result = "";
		// rtemp  100
		if (cmd == "RTEMP 100")
		{
			result = "RTEMP 100 ";

			for (const auto& v : vector_value)
			{
				result += "," + v;
			}
		}
		else if (cmd.find("RTEMP") != -1)
		{
			std::string getmsg;
			int index_slot = cmd.find(" ") + 1;
			getmsg = cmd.substr(index_slot);
			int nSlot = boost::lexical_cast<int>(getmsg) - 1;
			std::string value = vector_value[nSlot];

			result = "RTEMP " + getmsg + "," + value;

		}
		else
		{
			result = cmd;
		}

		result += ",1";
		return result;
	}

private:
	std::vector<std::string> vector_value;
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
		std::this_thread::sleep_for(std::chrono::milliseconds(delay_TCP));
		if (getmsg.length() > 0)
			sv->sendMsg(getmsg.c_str());
	}

	void tcp_delay(int second)
	{
		delay_TCP = second;
	}

private:
	server* sv = nullptr;
	int port_ = 0;
	int delay_TCP = 0;
};

