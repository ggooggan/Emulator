#ifndef Subject_H
#define Subject_H

#include "Observer.h"

#include <vector>
#include <mutex>

template <class T>
class Subject
{
public:
    Subject() {}
    virtual ~Subject() {}

    void attach(Observer<T>& observer)
    {
        std::lock_guard<std::mutex> guard(_addMutex);
        std::vector<Observer<T>*>::iterator itr_found = std::find(m_observers.begin(), m_observers.end(), &observer);
        if (itr_found == m_observers.end())
            m_observers.push_back(&observer);
    }

    void detach(Observer<T>& observer)
    {
        std::lock_guard<std::mutex> guard(_addMutex);

        std::vector<Observer<T>*>::iterator itr_found = std::find(m_observers.begin(), m_observers.end(), &observer);
        if (itr_found != m_observers.end())
            m_observers.erase(itr_found);
    }

    //void detachAll ()
    //{
    //   m_observers.clear();
    //}

    void notify()
    {
        std::vector<Observer<T>*>::iterator it;

        std::lock_guard<std::mutex> guard(_addMutex);

        for (it = m_observers.begin(); it != m_observers.end(); ++it) {
            (*it)->update(static_cast<T*>(this));
        }


        //clear();
    }

    //virtual void clear() = 0;

protected:
    std::mutex _sendMutex;

private:
    std::vector<Observer<T>*> m_observers;
    std::mutex _addMutex;
};

#endif // Subject_H
