
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

#ifndef _JSON_BINARY_VALUE_H_
#define _JSON_BINARY_VALUE_H_

namespace JSON {

class BinaryValue :
	public ValueT<BinaryType, BinaryDataType>
{
	friend class ValueFactory;

public:
	virtual ~BinaryValue() {}

	bool operator == (const BinaryValue& obj) const {return this->Equals(obj);}

	virtual BinaryType& ToBinary()	{return m_Value;}

	virtual StringType& ToString()
	{
		static StringType s;
		Base85::Encoder enc;
		enc.Encode(m_Value, s);
		return s;
	}

	virtual int Serialize(StringType& sf) const
	{
		StringType encoded;
		Base85::Encoder enc;
		int r = enc.Encode(m_Value, encoded);

		this->EscapeString(encoded, sf);
		sf.insert(0, L"\"base85:");
		sf += L'\"';
		return (errno = r);
	}

	virtual int Serialize(StringUTF8Type& sf) const
	{
		StringType encoded;
		Base85::Encoder enc;
		int r = enc.Encode(m_Value, encoded);

		this->EscapeString(encoded, sf);
		sf.insert(0, "\"base85:");
		sf += '\"';
		return (errno = r);
	}
};

}

#endif //_JSON_BINARY_VALUE_H_
