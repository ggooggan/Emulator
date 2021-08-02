
#pragma once
#include "Subject.h"
#include "Singleton.h"

//#include <mutex>

#include <stdarg.h>


class GRIPPERSubject :
    public Subject<GRIPPERSubject>
    , public Singleton<GRIPPERSubject>
{
public:
    std::string getMessage()
    {
        return _message;
    }
    void sendMessage(const std::string message, ...)
    {
        std::lock_guard<std::mutex> lock(_sendMutex);

        va_list argList;
        va_start(argList, message);
        _message = message;

        notify();
    }
private:
    std::string _message;
    friend Singleton;
};