
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

#include "json.h"

namespace JSON {

ArrayValue::~ArrayValue()
{
	for (ArrayType::iterator i = m_Value.begin(); i != m_Value.end(); ++i) delete (*i);
	m_Value.clear();
}

int ArrayValue::Set(const void *value)
{
	//Remove the old data
	for (ArrayType::iterator i = m_Value.begin(); i != m_Value.end(); ++i) delete (*i);
	m_Value.clear();

	//Copy the new data to this instance
	const ArrayType *pArray = static_cast<const ArrayType *>(value);
	m_Value.insert(m_Value.begin(), pArray->begin(), pArray->end());
	return 0;
}

int ArrayValue::Serialize(StringType& sf) const
{
	StringType str(L"[\n");
	ENTER_LEVEL();

	StringType ts;
	int r = 0;
	int j=0, count = m_Value.size();
	for (ArrayType::const_iterator i = m_Value.begin(); i != m_Value.end(); ++i, ++j) {
		str += m_CurrentPadding;

		r = (**i).Serialize(ts);
		if (r) return r;

		str += ts;

		if (j < (count-1))	str += L",\n";
		else				str += L'\n';
	}

	LEAVE_LEVEL();
	if (m_Value.size() > 0) {
		str += m_CurrentPadding;
		str += L']';
	} else {
		str[1] = L']';
	}

	sf = str;
	return r;
}

int ArrayValue::Serialize(StringUTF8Type& sf) const
{
	StringUTF8Type str("[\n");
	ENTER_LEVEL();

	StringUTF8Type ts;
	int r = 0;
	int j=0, count = m_Value.size();
	for (ArrayType::const_iterator i = m_Value.begin(); i != m_Value.end(); ++i, ++j) {
		str += m_CurrentPadding_UTF8;

		r = (**i).Serialize(ts);
		if (r) return r;

		str += ts;

		if (j < (count-1))	str += ",\n";
		else				str += '\n';
	}

	LEAVE_LEVEL();
	if (m_Value.size() > 0) {
		str += m_CurrentPadding_UTF8;
		str += ']';
	} else {
		str[1] = ']';
	}

	sf = str;
	return r;
}

int ArrayValue::Remove(int index)
{
	ArrayType::iterator i = m_Value.begin() + index;
	delete (*i);
	m_Value.erase(i);
	return (errno = 0);
}

}
