#pragma once
#include <mutex>
#include <atomic>

template <typename T>
class CLock
{
public:
	CLock() :
		m_pPtr(nullptr)
	{
	}
private:
	T m_pPtr;
	std::atomic<bool> _locked = false;

	std::mutex lock;
public:
	T Get()
	{
		bool expected = false;
		bool desired = true;

		while (!_locked.compare_exchange_strong(expected, desired))
		{
			expected = false;
		}
		return m_pPtr;
	}


public:
	void operator = (T pPtr)
	{
		m_pPtr = pPtr;
	}

	T operator -> ()
	{
		bool expected = false;
		bool desired = true;

		while (!_locked.compare_exchange_strong(expected, desired))
		{
			expected = false;
		}
		return m_pPtr;
	}

	T Threadlock()
	{
		bool expected = false;
		bool desired = true;

		while (!_locked.compare_exchange_strong(expected, desired))
		{
			expected = false;
		}
		return m_pPtr;
	}
	T Threadunlock()
	{
		_locked.store(false);
	}
	
};

