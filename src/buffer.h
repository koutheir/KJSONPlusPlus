
/*
Copyright 2011-2011 Koutheir Attouchi. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY KOUTHEIR ATTOUCHI ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL KOUTHEIR ATTOUCHI OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of Koutheir Attouchi.
*/

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
