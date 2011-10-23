
#ifndef _BASE_85_H_
#define _BASE_85_H_

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
	char		*m_EncodedData;

protected:
	void BeginEncoding(char* EncodedData);
	void Encode();
	void Encode(unsigned char c);
	void EndEncoding();

public:
	virtual ~Encoder() {}

	size_t GetEncodedSize(size_t Length) const;

	void Encode(const unsigned char* Data, size_t Length, char* EncodedData, size_t *EncodedLength = NULL);
	int Encode(const JSON::Buffer& Data, std::string& EncodedData);
	int Encode(const JSON::Buffer& Data, std::wstring& EncodedData);
};


/// Decodes textual data encoded using Base85 algorithm into binary data
class Decoder
{
protected:
	uint32_t		m_Tuple;
	int				m_Count, m_Length;
	unsigned char	*m_DecodedData;
	const char		*m_EncodedData;

	static uint32_t m_Power85[];

protected:
	void Decode();
	int DecodeData();

public:
	virtual ~Decoder() {}

	int Decode(const char* Data, size_t Length, unsigned char* DecodedData, size_t& DecodedLength, bool PreserveChar = false);
	int Decode(const char* Data, size_t Length, JSON::Buffer& DecodedData, bool PreserveChar = false);
	int Decode(const wchar_t* Data, size_t Length, JSON::Buffer& DecodedData, bool PreserveChar = false);
	int Decode(const std::string& Data, JSON::Buffer& DecodedData, bool PreserveChar = false);
	int Decode(const std::wstring& Data, JSON::Buffer& DecodedData, bool PreserveChar = false);
};

}

}

#endif
