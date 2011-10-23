
#include "base85_dec.h"

namespace JSON {

namespace Base85 {

uint32_t Decoder::m_Power85[] = {85 * 85 * 85 * 85, 85 * 85 * 85, 85 * 85, 85, 1};


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

}

}
