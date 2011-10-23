
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

#ifndef _JSON_DATE_TIME_VALUE_H_
#define _JSON_DATE_TIME_VALUE_H_

#include <memory.h>

inline bool operator == (const JSON::DateTimeType& v1, const JSON::DateTimeType& v2)
{
	return (memcmp(&v1, &v2, sizeof(v1)) == 0);
}

namespace JSON {

class DateTimeValue :
	public ValueT<DateTimeType, DateTimeDataType>
{
	friend class ValueFactory;

protected:
	DateTimeValue() {memset(&m_Value, 0, sizeof(m_Value));}

public:
	virtual ~DateTimeValue() {}

	bool operator == (const DateTimeValue& obj) const {return this->Equals(obj);}

	virtual DateTimeType& ToDateTime()	{return m_Value;}
	virtual StringType& ToString()		{static StringType s; ISO8601::ToString(m_Value, s); return s;}

	virtual int Serialize(StringType& sf) const
	{
		int r = ISO8601::ToString(m_Value, sf);
		sf.insert(0, 1, L'\"');
		sf += L'\"';
		return (errno = r);
	}
	virtual int Serialize(StringUTF8Type& sf) const
	{
		int r = ISO8601::ToString(m_Value, sf);
		sf.insert(0, 1, '\"');
		sf += '\"';
		return (errno = r);
	}
};

}

#endif //_JSON_DATE_TIME_VALUE_H_
