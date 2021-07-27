#ifndef Observer_H
#define Observer_H

template <class T>
class Observer
{
public:
	Observer() {};
	virtual ~Observer() {};
	virtual void update(T* subject) = 0;
};

#endif  //Observer_H
#pragma once
