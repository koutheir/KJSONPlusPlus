
#ifndef _BASE_85_ENCODER_H_
#define _BASE_85_ENCODER_H_

#include <stdlib.h>
#include <stdint.h>
#include <string>
#include "buffer.h"

namespace JSON {

namespace Base85 {

/// Encodes binary data into textual form based on Base85 algorithm
class Encoder
{
protected:
	uint32_t	m_Tuple;
	int			m_Count;
	void		*m_EncodedData;

protected:
	template<class T> void BeginEncoding(T* EncodedData);
	template<class T> void Encode();
	template<class T> void Encode(unsigned char c);
	template<class T> void EndEncoding();

public:
	virtual ~Encoder() {}

	size_t GetEncodedSize(size_t Length) const {return (4 + Length + (Length >> 2) + ((Length % 4) ? 1 : 0));}

	template<class T> void Encode(const unsigned char* Data, size_t Length, T* EncodedData, size_t *EncodedLength = NULL);
	template<class T> int Encode(const JSON::Buffer& Data, std::basic_string<T, std::char_traits<T>, std::allocator<T> >& EncodedData);
};


template<class T>
void Encoder::Encode()
{
	T * & EncodedData = *reinterpret_cast<T **>(&m_EncodedData);
	unsigned char buf[5];
	unsigned char *s = buf;
	int i = 5;

	do {
		*s++ = m_Tuple % 85;
		m_Tuple /= 85;
	} while (--i > 0);

	i = m_Count;
	do {
		*EncodedData++ = '!' + *--s;
	} while (i-- > 0);
}

template<class T>
void Encoder::Encode(unsigned char c)
{
	T * & EncodedData = *reinterpret_cast<T **>(&m_EncodedData);

	switch (m_Count++) {
	case 0:	m_Tuple |= (c << 24); break;
	case 1: m_Tuple |= (c << 16); break;
	case 2:	m_Tuple |= (c <<  8); break;
	case 3:
		m_Tuple |= c;
		if (m_Tuple == 0)
			*EncodedData++ = 'z';
		else
			this->Encode<T>();
		m_Tuple = 0;
		m_Count = 0;
		break;
	}
}

template<class T>
void Encoder::BeginEncoding(T* encoded_data)
{
	T * & EncodedData = *reinterpret_cast<T **>(&m_EncodedData);

	m_Tuple = 0;
	m_Count = 0;
	m_EncodedData = encoded_data;

	*EncodedData++ = '<';
	*EncodedData++ = '~';
}

template<class T>
void Encoder::EndEncoding()
{
	T * & EncodedData = *reinterpret_cast<T **>(&m_EncodedData);
	if (m_Count > 0) this->Encode<T>();

	*EncodedData++ = '~';
	*EncodedData++ = '>';
}

template<class T>
void Encoder::Encode(const unsigned char* Data, size_t Length, T* EncodedData, size_t *EncodedLength)
{
	if (EncodedLength != NULL) *EncodedLength = this->GetEncodedSize(Length);

	this->BeginEncoding<T>(EncodedData);
	for (size_t i=0; i<Length; ++i) this->Encode<T>(*Data++);
	this->EndEncoding<T>();
}

template<class T>
int Encoder::Encode(const JSON::Buffer& Data, std::basic_string<T, std::char_traits<T>, std::allocator<T> >& EncodedData)
{
	size_t EncodedLength = this->GetEncodedSize(Data.Size());
	EncodedData.resize(EncodedLength, '\0');
	if (EncodedData.size() < EncodedLength) return (errno = ENOMEM);

	this->Encode(Data.Data(), Data.Size(), const_cast<T *>(EncodedData.c_str()));
	return (errno = 0);
}

}

}

#endif
