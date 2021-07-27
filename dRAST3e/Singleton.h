#ifndef Singleton_H
#define Singleton_H

template <typename T>

class Singleton
{
public:
	static T* getInstancePtr()
	{
		if (_instance == nullptr)
			if (_instance == nullptr)
			{
				_instance = new T();
				atexit(destroy);
			}

		return _instance;
	}

	static T& getInstance()
	{
		if (_instance == nullptr)
			if (_instance == nullptr)
			{
				_instance = new T();
				atexit(destroy);
			}

		return *_instance;
	}

protected:
	Singleton() {};
	virtual ~Singleton() {};

private:
	static void destroy()
	{
		if (_instance != nullptr)
		{
			delete _instance;
			_instance = nullptr;
		}

	}

private:
	static T* _instance;
};

template <typename T> T* Singleton<T>::_instance = nullptr;

#endif // Singleton_H
