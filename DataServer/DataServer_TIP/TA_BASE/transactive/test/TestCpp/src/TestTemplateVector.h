#ifndef  __CLASS_TEST_TEMPLATE_VECTOR__HH__
#define  __CLASS_TEST_TEMPLATE_VECTOR__HH__

#include <iostream>
#include <string>
#include <stdio.h>

template<typename T>
class tcontainer
{
public:
	virtual void push(const T&) = 0;
	virtual void pop() = 0;
	virtual const T& begin() = 0;
	virtual const T& end() = 0;
	virtual size_t size() = 0;
};



template<typename T>
class tvector : public tcontainer<T>
{
private:
	size_t m_size;
	size_t m_cap;
	T* m_buf;
public:
	static const size_t _step = 100;
public:
	tvector()
	{
		m_size = 0;
		m_cap = _step;
		m_buf = NULL;
		re_capacity(m_cap);
		
	}
	~tvector()
	{
		if (NULL != m_buf)
		{
			free(m_buf);
			m_buf = NULL;
		}
	}
	void re_capacity(size_t s)
	{
		if (NULL != m_buf)
		{
			m_buf = (T*)malloc(sizeof(T) * s);
		}
		else
		{
			free(m_buf);
			m_buf = NULL;
			m_buf = (T*)malloc(sizeof(T) * s);
		}
	}
	
	virtual void push(const T& v)
	{
		if (m_size >= m_cap)
		{
			re_capacity(m_cap += _step);
			m_buf[m_size++] = v;
		}
	}

	virtual void pop()
	{
		if (m_size)
		{
			m_size--;
		}
	}

	virtual const T& begin()
	{
		return buf[0];
	}

	virtual const T& end()
	{
		if (m_size > 0)
		{
			return m_buf[m_size - 1];
		}
	}

	virtual size_t size()
	{
		return m_size;
	}

	const T& operator[] (size_t nIndex)
	{
		if (nIndex >= 0 && nIndex < m_size)
		{
			return m_buf[nIndex];
		}
	}

	/*
	void do_Test()
	{
		tvector<int> v;
		for (int nIndex = 0; nIndex < 1000; ++nIndex)
		{
			v.push(nIndex);
		}

		for (int nIndex = 0; nIndex < 1000; ++nIndex)
		{
			std::cout<<v[nIndex]<<std::endl;
		}
	}
	*/

};

#endif//__CLASS_TEST_TEMPLATE_VECTOR__HH__



