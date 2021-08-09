#pragma once
#include "tcp.h"
#include "Singleton.h"
#include "TCP_subject.h"
#include "ADP_subject.h"

class adp_command : public Singleton<adp_command>
{
public:
	bool bTipAligner = false;



	std::string check_Command(const std::string cmd)
	{
		std::string result = "";

		result = cmd;

		// 1,1 dispensing table
		// 1,2 Cooling table
		// 2,#, 4#

		int index_space = cmd.find(" ");
		std::string command = cmd.substr(0, index_space);
		std::string command_value = cmd.substr(index_space + 1);

		if (command == "ADPP") 
		{
			if (command_value == "9,4,1,1")
			{
				// 원래 이후 TRM일 때, check 해야 하는데. 정확한 값을 알 수가 없어서...
				bTipAligner = true;
				ADPSubject::getInstance().sendMessage("ALIGNER@ON");
			}
		}
		else if (command == "ADPF")
		{
			if (command_value == "9,4,1,1")
			{
				bTipAligner = false;
				ADPSubject::getInstance().sendMessage("ALIGNER@OFF");
			}
		}
		else
		{

		}
		result += ",1";
		return result;
	}

};

class unit_adp : public Singleton<unit_adp>, public Observer<TCPSubject>
{
public:
	void thread_connect(int port)
	{
		TCPSubject::getInstance().attach(*this);
		port_ = port;

		auto th_connect = std::thread([&]() {

			boost::asio::io_context io_context;
			sv = new server(io_context, port_, "adp");
			io_context.run();

			});

		th_connect.detach();
	}

	virtual void update(TCPSubject* subject)
	{
		std::string message = subject->getMessage();
		int rx_message = message.find("rx");
		int moduel_message = message.find("adp");

		if (rx_message != -1 && moduel_message != -1)
			checkMsg(message);
	}

	void checkMsg(std::string& msg)
	{

		// message check;
		std::string getmsg = msg;
		int aa = msg.find("]") + 2;
		getmsg = msg.substr(aa);


		/* return message */
		getmsg = adp_command::getInstance().check_Command(getmsg);

		/* send message */
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