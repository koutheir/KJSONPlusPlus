
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

#include "json.h"

namespace JSON {

BooleanType StringValue::ToBoolean()
{
	if (!wcscasecmp(m_Value.c_str(), m_False.c_str()) ||
		!wcscasecmp(m_Value.c_str(), L"0") ||
		!wcscasecmp(m_Value.c_str(), L"off") ||
		!wcscasecmp(m_Value.c_str(), L"no")) return false;

	if (!wcscasecmp(m_Value.c_str(), m_True.c_str()) ||
		!wcscasecmp(m_Value.c_str(), L"1") ||
		!wcscasecmp(m_Value.c_str(), L"on") ||
		!wcscasecmp(m_Value.c_str(), L"yes")) return true;

	return const_cast<BooleanType&>(m_NullBoolean);
}

IntegerType StringValue::ToInteger()
{
	wchar_t *p=NULL;
	return wcstoll(m_Value.c_str(), &p, 10);
}

DoubleType StringValue::ToDouble()
{
	wchar_t *p=NULL;
	return wcstod(m_Value.c_str(), &p);
}

DateTimeType& StringValue::ToDateTime()
{
	static DateTimeType v;
	memset(&v, 0, sizeof(v));
	ISO8601::FromString(v, m_Value);
	return v;
}

template<class T>
int StringValue::SerializeT(std::basic_string<T, std::char_traits<T>, std::allocator<T> >& sf) const
{
	T *escaped_str;
	int len;

	this->EscapeString<T>(m_Value.c_str(), m_Value.length(), &escaped_str, &len);

	sf = (T)'\"';
	sf.append(escaped_str, len);
	sf += (T)'\"';

	free(escaped_str);
	return 0;
}

int StringValue::Serialize(StringType& sf) const
{
	return this->SerializeT<wchar_t>(sf);
}

int StringValue::Serialize(StringUTF8Type& sf) const
{
	return this->SerializeT<char>(sf);
}

}
