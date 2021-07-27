#pragma once
#include "TCP_subject.h"

class test : public Observer<TCPSubject>
{
public:
	test();
	virtual void update(TCPSubject* subject);
};

test::test() {
	TCPSubject::getInstance().attach(*this);
}

void test::update(TCPSubject* subject) {
	std::string message = subject->getMessage();
	
}