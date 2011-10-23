
/*
Copyright 2011-2011 Koutheir Attouchi. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE FREEBSD PROJECT ``AS IS'' AND ANY EXPRESS OR
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

#include "buffer.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>


namespace JSON {


Buffer::Buffer(size_t size, size_t capacity) :
	m_size(0), m_capacity(0), m_data(NULL), m_ownership(true)
{
	this->Resize(size, capacity);
}

Buffer::Buffer(const void * data, size_t size) :
	m_size(0), m_capacity(0), m_data(NULL), m_ownership(true)
{
	if (!this->Resize(size)) return;
	memmove(m_data, data, size);
}

Buffer::Buffer(const void * data, size_t size, size_t capacity) :
	m_size(0), m_capacity(0), m_data(NULL), m_ownership(true)
{
	if (!this->Resize(size, capacity)) return;
	memmove(m_data, data, size);
}

Buffer::Buffer(void * data, size_t size, size_t capacity, bool take_ownership) :
	m_size(size), m_capacity(capacity), m_data((unsigned char *)data), m_ownership(take_ownership)
{
}

Buffer::Buffer(const Buffer& obj) :
	m_size(0), m_capacity(0), m_data(NULL), m_ownership(true)
{
	this->Assign(obj.Data(), obj.Size(), obj.Capacity());
}

void Buffer::Swap(Buffer& obj)
{
	Buffer interm(m_data, m_size, m_capacity, m_ownership);
	this->Detach();

	this->Assign(obj.m_data, obj.m_size, obj.m_capacity, obj.m_ownership);
	obj.Detach();

	obj.Assign(interm.m_data, interm.m_size, interm.m_capacity, interm.m_ownership);
	interm.Detach();
}

void * Buffer::Detach()
{
	void * data = m_data;
	m_data = NULL;
	m_size = m_capacity = 0;
	m_ownership = false;
	return data;
}

int Buffer::Assign(const void* data, size_t size, size_t capacity)
{
	int r = this->Resize(size, capacity);
	if (r) return r;

	memmove(m_data, data, size);
	m_ownership = true;
	return (errno = 0);
}

int Buffer::Assign(void* data, size_t size, size_t capacity, bool take_ownership)
{
	this->Resize(0, 0);

	m_data = (unsigned char *)data;
	m_size = size;
	m_capacity = capacity;
	m_ownership = take_ownership;
	return (errno = 0);
}

int Buffer::Append(const void* data, size_t size)
{
	size_t old_size = m_size, new_size = m_size + size;

	if (m_capacity < new_size) {
		int r = this->Resize(old_size, new_size);
		if (r) return r;
	}

	memmove(m_data + old_size, data, size);
	m_size = new_size;
	return (errno = 0);
}

int Buffer::Resize(size_t size, size_t capacity)
{
	if (capacity < size) capacity = size;

	if (!capacity) {
		free(m_data);
		m_data = NULL;
	} else {
		void * p = realloc(m_data, capacity);
		if (!p) return errno;
		m_data = (unsigned char *)p;
	}

	m_capacity = capacity;
	m_size = size;
	return (errno = 0);
}

bool Buffer::operator == (const Buffer& obj) const
{
	if (m_size != obj.m_size) return false;
	return (memcmp(m_data, obj.m_data, m_size) == 0);
}

}
