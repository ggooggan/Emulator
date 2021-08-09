#pragma once
#include "tcp.h"
#include "Singleton.h"
#include "TCP_subject.h"
#include <vector>
#include <boost/lexical_cast.hpp>

class io_command : public Singleton<io_command>
{
public:
	void setValue(std::string &bar01, std::string& bar02, std::vector<int> io_Value)
	{
		barout_1 = bar01;
		barout_2 = bar02;
		ioValue = io_Value;
	}

	std::string check_Command(const std::string cmd)
	{
		std::string result = "";

		result = cmd;

		int index_space = cmd.find(" ");
		std::string command = cmd.substr(0, index_space);
		std::string command_value = cmd.substr(index_space + 1);

		if (command == "BAROUT")
		{
			if (command_value == "")
				result = "BAROUT " + barout_1;
			else if (command_value == "2")
				result = "BAROUT " + barout_2;
		}
		else if (command == "RIP")
		{
			std::string getmsg;
			int aa = cmd.find(" ") + 1;
			getmsg = cmd.substr(aa);
			int nSlot = boost::lexical_cast<int>(getmsg);
			int nSlot_status = ioValue[nSlot];
			result = "RIP " + getmsg + "," + boost::lexical_cast<std::string>(nSlot_status);
		}
		else if (cmd.find("PANELCHECK") != -1)
		{
			// Panel check에 관한 리턴 명령어 수행
			
			// 1,1 -> dispensing
			// 2,1 -> cooling dispensing
			// 3,1 -> optic
			// 5,1 -> gripper

			if (command_value == "5,1")
			{
				if (gripper_command::getInstance().panelCheck_gripper == true)
					result = "PANELCHECK 5,1,1";
				else
					result = "PANELCHECK 5,1,0";
			}
			
			if (command_value == "1,1")
			{
				if (gripper_command::getInstance().panelCheck_dispensing == true)
					result = "PANELCHECK 1,1,1";
				else
					result = "PANELCHECK 1,1,0";
			}

			if (command_value == "2,1")
			{
				if (gripper_command::getInstance().panelCheck_cooling == true)
					result = "PANELCHECK 2,1,1";
				else
					result = "PANELCHECK 2,1,0";
			}

			if (command_value == "3,1")
			{
				if (gripper_command::getInstance().panelCheck_optic == true)
					result = "PANELCHECK 3,1,1";
				else
					result = "PANELCHECK 3,1,0";
			}
		}

		result += ",1";
		return result;
	}

private:
	std::string barout_1 = "";
	std::string barout_2 = "";
	bool check_barcode = false; // barcode 수행 여부 확인
	std::vector<int> ioValue;
};

class unit_io : public Singleton<unit_io>, public Observer<TCPSubject>
{
public:
	void thread_connect(int port)
	{
		TCPSubject::getInstance().attach(*this);
		port_ = port;
		auto th_connect = std::thread([&]() {

			boost::asio::io_context io_context;
			sv = new server(io_context, port_, "io");
			io_context.run();

			});

		th_connect.detach();
	}

	virtual void update(TCPSubject* subject)
	{
		std::string message = subject->getMessage();
		int rx_message = message.find("rx");
		int moduel_message = message.find("io");

		if (rx_message != -1 && moduel_message != -1)
			checkMsg(message);
	}

	void checkMsg(std::string& msg)
	{
		// message check;
		std::string getmsg = msg;
		int aa = msg.find("]") + 2;
		getmsg = msg.substr(aa);

		getmsg = io_command::getInstance().check_Command(getmsg);

		if(getmsg.length() > 0)
			sv->sendMsg(getmsg.c_str());
	}
private:
	server* sv = nullptr;
	int port_ = 0;
};