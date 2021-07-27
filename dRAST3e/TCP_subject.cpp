#include "pch.h"
#include "TCP_subject.h"

std::string TCPSubject::getMessage() {
	return _message;
}

void TCPSubject::sendMessage(const std::string message, ...)
{
	std::lock_guard<std::mutex> lock(_sendMutex);

	va_list argList;

	va_start(argList, message);

	/*std::string msg = formatString(message, argList);*/

	_message = message;
	//_debugLevel = debugLevel;

	notify();
}