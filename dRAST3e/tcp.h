#pragma once

//https://glowcyan.blogspot.com/2019/07/c-boost-asio-tcp.html

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "TCP_subject.h"

using boost::asio::ip::tcp;

class session
	: public std::enable_shared_from_this<session>
{
public:
	session(tcp::socket socket, char* name)
		: socket_(std::move(socket)), moduleName(name)
	{
	}

	void start()
	{
		do_read();
	}

	void sendMsg(const char* data)
	{
		do_write(data);
	}

private:
	void sendMessage(std::string data, std::string type) {

		int length = data.length();

		// РќДо
		if (moduleName == "adp")
		{
			TCPSubject::getInstance().sendMessage("[adp, " + type + "] " + data.substr(0, length));
		}
		else if (moduleName == "gripper")
		{
			TCPSubject::getInstance().sendMessage("[gripper, " + type + "] " + data.substr(0, length));
		}
		else if (moduleName == "stage")
		{
			TCPSubject::getInstance().sendMessage("[stage, " + type + "] " + data.substr(0, length));
		}
		else if (moduleName == "temperature")
		{
			TCPSubject::getInstance().sendMessage("[temperature, " + type + "] " + data.substr(0, length));
		}
		else if (moduleName == "io")
		{
			TCPSubject::getInstance().sendMessage("[io, " + type + "] " + data.substr(0, length));
		}
		
	}

	void do_read()
	{
		auto self(shared_from_this());

		socket_.async_read_some(boost::asio::buffer(data_, max_length),
			[&, self](boost::system::error_code ec, std::size_t length)
			{
				if (!ec)
				{
					std::string str(data_);

					int aa = str.find("\r");
					std::string rx = str.substr(0, aa);

					sendMessage(rx, "rx");
					do_read();
				}
			});
	}

	void do_write(const char* data)
	{
		do_read();

		std::string str(data);
		txMsg = str;
		str += "\r\n";

		auto self(shared_from_this());
		
		boost::asio::async_write(socket_, boost::asio::buffer(str.c_str(), str.length()),
			[&](boost::system::error_code ec, std::size_t /*length*/)
			{
				if (!ec)
				{
					sendMessage(txMsg, "tx");
				}
			});
	}

	tcp::socket socket_;
	enum { max_length = 1024 };
	char data_[max_length];
	std::string txMsg = "";
	std::string rxMsg = "";
	
	char* moduleName = nullptr;
};

class server
{
public:
	server(boost::asio::io_context& io_context, short port, char* name)
		: acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), moduleName(name)
	{
		accept();
	}

	void sendMsg(const char* data)
	{
		test->sendMsg(data);
	}

	void delay_TCP(int time)
	{
		
	}
private:
	void accept()
	{
		acceptor_.async_accept(
			[&](boost::system::error_code ec, tcp::socket socket)
			{
				if (!ec)
				{
					test = std::make_shared<session>(std::move(socket), moduleName);
					test->start();
					
					TCPSubject::getInstance().sendMessage("[connect] " + std::string(moduleName));
				}
				else
				{
					TCPSubject::getInstance().sendMessage("[connect,fail] " + std::string(moduleName));
				}
			});
	}
	std::shared_ptr<session> test;
	tcp::acceptor acceptor_;
	char* moduleName = "";
};