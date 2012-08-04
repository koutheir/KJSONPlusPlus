
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

#ifndef _BASE_85_DECODER_H_
#define _BASE_85_DECODER_H_

#include <stdlib.h>
#include <stdint.h>
#include <string>
#include "buffer.h"

namespace JSON {

namespace Base85 {

/// Decodes textual data encoded using Base85 algorithm into binary data
class Decoder
{
protected:
	uint32_t		m_Tuple;
	int				m_Count, m_Length;
	unsigned char	*m_DecodedData;
	const void		*m_EncodedData;

	static uint32_t m_Power85[];

protected:
	void Decode();
	template<class T> int DecodeData();

public:
	virtual ~Decoder() {}

	template<class T> int Decode(const T* Data, size_t Length, unsigned char* DecodedData, size_t& DecodedLength, bool PreserveChar = false);
	template<class T> int Decode(const T* Data, size_t Length, JSON::Buffer& DecodedData, bool PreserveChar = false);
	template<class T> int Decode(const std::basic_string<T, std::char_traits<T>, std::allocator<T> >& Data, JSON::Buffer& DecodedData, bool PreserveChar = false)
		{return this->Decode(Data.c_str(), Data.length(), DecodedData, PreserveChar);}
};


template<class T>
int Decoder::DecodeData()
{
	m_Tuple = 0;
	m_Count = 0;

	const T * & EncodedData = *reinterpret_cast<const T **>(&m_EncodedData);
	const T *DataEnd = static_cast<const T *>(m_EncodedData) + m_Length;
	T c;

	for (;;) {
		if (EncodedData >= DataEnd)
			return (errno = EILSEQ);	//Error: Too short ascii85 section

		switch (c = *EncodedData++) {
		case '~':
			if (*EncodedData++ == '>') {
				if (m_Count > 0) {
					m_Count--;
					m_Tuple += m_Power85[m_Count];
					this->Decode();
				}
				c = *EncodedData++;
				return (errno = 0);
			}
			return (errno = EILSEQ);	//Error: '~' without '>' in ascii85 section

		case 'z':
			if (m_Count != 0)
				return (errno = EILSEQ);	//Error: 'z' inside ascii85 5-tuple

			*m_DecodedData++ = '\0';
			*m_DecodedData++ = '\0';
			*m_DecodedData++ = '\0';
			*m_DecodedData++ = '\0';
			break;

		case '\n': case '\r': case '\t': case ' ':
		case '\0': case '\f': case '\b': case 0x7F:
			break;

		default:
			if (c < '!' || c > 'u')
				return (errno = EILSEQ);	//Error: Unexpected character in ascii85 region

			m_Tuple += (c - '!') * m_Power85[m_Count++];
			if (m_Count == 5) {
				m_Count = 4;
				this->Decode();

				m_Count = 0;
				m_Tuple = 0;
			}
			break;
		}
	}
	return (errno = EILSEQ);
}

template<class T>
int Decoder::Decode(const T* Data, size_t Length, unsigned char* DecodedData, size_t& DecodedLength, bool PreserveChar)
{
	m_EncodedData = Data;
	m_Length = Length;
	m_DecodedData = DecodedData;

	DecodedLength = 0;

	const T * & EncodedData = *reinterpret_cast<const T **>(&m_EncodedData);
	const T *DataEnd = EncodedData + Length;
	T c;
	int r;

	while (EncodedData < DataEnd) {
		if ((c = *EncodedData++) == '<') {
			if ((c = *EncodedData++) == '~') {
				if ((r = this->DecodeData<T>())) return r;
			} else {
				if (PreserveChar) *m_DecodedData++ = '<';
				if (EncodedData >= DataEnd) break;
				if (PreserveChar) *m_DecodedData++ = (char)c;
			}
		} else if (PreserveChar)
			*m_DecodedData++ = (char)c;
	}

	DecodedLength = (m_DecodedData - DecodedData);
	return (errno = 0);
}

template<class T>
int Decoder::Decode(const T* Data, size_t Length, JSON::Buffer& DecodedData, bool PreserveChar)
{
	JSON::Buffer DecodedBuffer(Length - 4);
	if (DecodedBuffer.Size() < (Length - 4)) return (errno = ENOMEM);

	size_t len = 0;
	int r = this->Decode(Data, Length, DecodedBuffer.Data(), len, PreserveChar);
	if (r) return r;

	DecodedBuffer.Resize(len);
	DecodedBuffer.Swap(DecodedData);
	return (errno = 0);
}

}

}

#endif
