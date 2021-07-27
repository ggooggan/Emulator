#pragma once

//https://glowcyan.blogspot.com/2019/07/c-boost-asio-tcp.html

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
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

private:
    void do_read()
    {
        auto self(shared_from_this());

        socket_.async_read_some(boost::asio::buffer(data_, max_length),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    do_write(length);
                }
            });
    }

    void do_write(std::size_t length)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        auto self(shared_from_this());

        if (moduleName == "adp")
        {
            TCPSubject::getInstance().sendMessage("adp_message");
        }
        else
        {
            TCPSubject::getInstance().sendMessage("no");
        }

        
        data_[0] = 'H';
        boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
            [this, self](boost::system::error_code ec, std::size_t /*length*/)
            {
                if (!ec)
                {
                    do_read();
                }
            });
    }

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
    char* moduleName = "";
};

class server
{
public:
    server(boost::asio::io_context& io_context, short port, char* name)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), moduleName(name)
    {
        accept();
    }

private:
    void accept()
    {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    std::make_shared<session>(std::move(socket), moduleName)->start();
                }
            });
    }

    tcp::acceptor acceptor_;
    char* moduleName = "";
};