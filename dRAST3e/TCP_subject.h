#pragma once
#include "Subject.h"
#include "Singleton.h"

//#include <mutex>

#include <stdarg.h>


class TCPSubject :
    public Subject<TCPSubject>
    , public Singleton<TCPSubject>
{
public:
    std::string getMessage();
    //void setDebugLevelEnv();
    void sendMessage(const std::string message, ...);

private:
    std::string _message;
    friend Singleton;
};