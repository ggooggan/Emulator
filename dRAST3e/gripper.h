#pragma once
#include "tcp.h"
#include "Singleton.h"
#include "TCP_subject.h"
#include "GRIPPER_subject.h"

class gripper_command : public Singleton<gripper_command>
{
public:
	bool panelCheck_gripper = false;
	bool panelCheck_dispensing = false;
	bool panelCheck_cooling = false;
	bool panelCheck_optic = false;

	void panelCheck_init()
	{
		panelCheck_gripper = false;
		panelCheck_dispensing = false;
		panelCheck_cooling = false;
		panelCheck_optic = false;
	}

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
		if (command == "GET")
		{
			// led off
			if (command_value == "1,1")
			{
				GRIPPERSubject::getInstance().sendMessage("DISPENSING@OFF");
				GRIPPERSubject::getInstance().sendMessage("GRIPPER@ON");
				panelCheck_dispensing = false;
			}
			else if (command_value == "1,2")
			{
				GRIPPERSubject::getInstance().sendMessage("COOLING@OFF");
				GRIPPERSubject::getInstance().sendMessage("GRIPPER@ON");
				panelCheck_cooling = false;
			}
			else if (command_value[0] == '2')GRIPPERSubject::getInstance().sendMessage("GRIPPER@ON");
			else if (command_value[0] == '3')
			{
				GRIPPERSubject::getInstance().sendMessage("GRIPPER@ON");
				GRIPPERSubject::getInstance().sendMessage("STAGE@OFF");
				panelCheck_optic = false;
			}
			else if (command_value[0] == '4')GRIPPERSubject::getInstance().sendMessage("GRIPPER@ON");

			panelCheck_gripper = true;
		}
		else if (command == "PUT")
		{
			// led on
			if (command_value == "1,1")
			{
				GRIPPERSubject::getInstance().sendMessage("DISPENSING@ON");
				GRIPPERSubject::getInstance().sendMessage("GRIPPER@OFF");
				panelCheck_dispensing = true;
			}
			else if (command_value == "1,2")
			{
				GRIPPERSubject::getInstance().sendMessage("COOLING@ON");
				GRIPPERSubject::getInstance().sendMessage("GRIPPER@OFF");
				panelCheck_cooling = true;
			}
			else if (command_value[0] == '2')GRIPPERSubject::getInstance().sendMessage("GRIPPER@OFF");
			else if (command_value[0] == '3')
			{
				GRIPPERSubject::getInstance().sendMessage("GRIPPER@OFF");
				GRIPPERSubject::getInstance().sendMessage("STAGE@ON");
				panelCheck_optic = true;
			}
			else if (command_value[0] == '4')GRIPPERSubject::getInstance().sendMessage("GRIPPER@OFF");

			panelCheck_gripper = false;
		}


		result += ",1";
		return result;
	}
};

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

		/* send message */
		if (getmsg.length() > 0)
			sv->sendMsg(getmsg.c_str());
	}
private:
	server* sv = nullptr;
	int port_ = 0;

};