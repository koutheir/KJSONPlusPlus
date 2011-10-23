
#include "utf8.h"
#include "base85.h"
#include <errno.h>

namespace JSON {

namespace Base85 {

uint32_t Decoder::m_Power85[] = {85 * 85 * 85 * 85, 85 * 85 * 85, 85 * 85, 85, 1};


size_t Encoder::GetEncodedSize(size_t Length) const
{
	return (4 + Length + (Length >> 2) + ((Length % 4) ? 1 : 0));
}

void Encoder::Encode()
{
	int i = 5;
	char buf[5], *s = buf;

	do {
		*s++ = m_Tuple % 85;
		m_Tuple /= 85;
	} while (--i > 0);

	i = m_Count;
	do {
		*m_EncodedData++ = '!' + *--s;
	} while (i-- > 0);
}

void Encoder::Encode(unsigned char c)
{
	switch (m_Count++) {
	case 0:	m_Tuple |= (c << 24); break;
	case 1: m_Tuple |= (c << 16); break;
	case 2:	m_Tuple |= (c <<  8); break;
	case 3:
		m_Tuple |= c;
		if (m_Tuple == 0)
			*m_EncodedData++ = 'z';
		else
			this->Encode();
		m_Tuple = 0;
		m_Count = 0;
		break;
	}
}

void Encoder::BeginEncoding(char* EncodedData)
{
	m_Tuple = 0;
	m_Count = 0;
	m_EncodedData = EncodedData;

	*m_EncodedData++ = '<';
	*m_EncodedData++ = '~';
}

void Encoder::EndEncoding()
{
	if (m_Count > 0) this->Encode();

	*m_EncodedData++ = '~';
	*m_EncodedData++ = '>';
}

void Encoder::Encode(const unsigned char* Data, size_t Length, char* EncodedData, size_t *EncodedLength)
{
	if (EncodedLength != NULL) *EncodedLength = this->GetEncodedSize(Length);

	this->BeginEncoding(EncodedData);
	for (size_t i=0; i<Length; ++i) this->Encode(*Data++);
	this->EndEncoding();
}

int Encoder::Encode(const JSON::Buffer& Data, std::string& EncodedData)
{
	size_t EncodedLength = this->GetEncodedSize(Data.Size());
	EncodedData.resize(EncodedLength, '\0');
	if (EncodedData.size() < EncodedLength) return (errno = ENOMEM);

	this->Encode(Data.Data(), Data.Size(), const_cast<char *>(EncodedData.c_str()));
	return (errno = 0);
}

int Encoder::Encode(const JSON::Buffer& Data, std::wstring& EncodedData)
{
	std::string str;
	int r = this->Encode(Data, str);
	if (r) return r;

	return JSON::UTF8::ToUnicode(str.c_str(), str.length(), EncodedData);
}

void Decoder::Decode()
{
	switch (m_Count) {
	case 4:
		*m_DecodedData++ = (m_Tuple >> 24);
		*m_DecodedData++ = (m_Tuple >> 16);
		*m_DecodedData++ = (m_Tuple >>  8);
		*m_DecodedData++ = m_Tuple;
		break;

	case 3:
		*m_DecodedData++ = (m_Tuple >> 24);
		*m_DecodedData++ = (m_Tuple >> 16);
		*m_DecodedData++ = (m_Tuple >>  8);
		break;

	case 2:
		*m_DecodedData++ = (m_Tuple >> 24);
		*m_DecodedData++ = (m_Tuple >> 16);
		break;

	case 1:
		*m_DecodedData++ = (m_Tuple >> 24);
		break;
	}
}

int Decoder::DecodeData()
{
	m_Tuple = 0;
	m_Count = 0;

	const char *DataEnd = m_EncodedData + m_Length;
	char c;

	for (;;) {
		if (m_EncodedData >= DataEnd)
			return (errno = EILSEQ);	//Error: Too short ascii85 section

		switch (c = *m_EncodedData++) {
		case '~':
			if (*m_EncodedData++ == '>') {
				if (m_Count > 0) {
					m_Count--;
					m_Tuple += m_Power85[m_Count];
					this->Decode();
				}
				c = *m_EncodedData++;
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

int Decoder::Decode(const char* Data, size_t Length, unsigned char* DecodedData, size_t& DecodedLength, bool PreserveChar)
{
	m_EncodedData = Data;
	m_Length = Length;
	m_DecodedData = DecodedData;

	DecodedLength = 0;

	const char *DataEnd = m_EncodedData + Length;
	char c;
	int r;

	while (m_EncodedData < DataEnd) {
		if ((c = *m_EncodedData++) == '<') {
			if ((c = *m_EncodedData++) == '~') {
				if ((r = this->DecodeData())) return r;
			} else {
				if (PreserveChar) *m_DecodedData++ = '<';
				if (m_EncodedData >= DataEnd) break;
				if (PreserveChar) *m_DecodedData++ = c;
			}
		} else if (PreserveChar)
			*m_DecodedData++ = c;
	}

	DecodedLength = (m_DecodedData - DecodedData);
	return (errno = 0);
}

int Decoder::Decode(const char* Data, size_t Length, JSON::Buffer& DecodedData, bool PreserveChar)
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

int Decoder::Decode(const wchar_t* Data, size_t Length, JSON::Buffer& DecodedData, bool PreserveChar)
{
	char *str = NULL;
	int r, len = 0;
	
	if ((r = JSON::UTF8::FromUnicode(Data, Length, &str, &len))) return r;
	r = this->Decode(str, len, DecodedData, PreserveChar);
	free(str);
	return (errno = r);
}

int Decoder::Decode(const std::string& Data, JSON::Buffer& DecodedData, bool PreserveChar)
{
	return this->Decode(Data.c_str(), Data.length(), DecodedData, PreserveChar);
}

int Decoder::Decode(const std::wstring& Data, JSON::Buffer& DecodedData, bool PreserveChar)
{
	return this->Decode(Data.c_str(), Data.length(), DecodedData, PreserveChar);
}

}

}
