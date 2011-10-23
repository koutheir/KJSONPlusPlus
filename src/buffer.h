
#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <memory.h>

namespace JSON {


class Buffer
{
protected:
	size_t			m_size, m_capacity;
	unsigned char	*m_data;
	bool			m_ownership;
	int				m_allocation_policy;

public:
	Buffer(size_t size = 0, size_t capacity = 0);
	Buffer(const void * data, size_t size);
	Buffer(const void * data, size_t size, size_t capacity);
	Buffer(void * data, size_t size, size_t capacity, bool take_ownership);
	Buffer(const Buffer&);

	virtual ~Buffer()					{if (m_ownership) this->Resize(0, 0);}

	void Swap(Buffer&);
	void * Detach();

	int Assign(const void* data, size_t size, size_t capacity = 0);
	int Assign(void* data, size_t size, size_t capacity, bool take_ownership);

	int Append(const void* data, size_t size);
	int Append(const Buffer& obj)		{return this->Append(obj.m_data, obj.m_size);}

	size_t Size() const					{return m_size;}
	size_t Capacity() const				{return m_capacity;}
	int Resize(size_t size, size_t capacity = 0);

	bool Owner() const					{return m_ownership;}
	bool Empty() const					{return (m_size == 0);}
	void Clear()						{this->Fill(0);}
	void Fill(unsigned char value = 0)	{memset(m_data, value, m_size);}

	unsigned char * Data()				{return m_data;}
	const unsigned char * Data() const	{return m_data;}

	unsigned char& operator[] (size_t index)		{return m_data[index];}
	unsigned char operator[] (size_t index) const	{return m_data[index];}
	unsigned char& At(size_t index)					{return m_data[index];}
	unsigned char At(size_t index) const			{return m_data[index];}

	Buffer& operator = (const Buffer& obj)			{this->Assign(obj.Data(), obj.Size(), obj.Capacity()); return (*this);}

	Buffer& operator += (const Buffer& obj)			{this->Append(obj); return (*this);}

	bool operator == (const Buffer& obj) const;
	bool operator != (const Buffer& obj) const		{return !((*this) == obj);}
};

}

#endif
