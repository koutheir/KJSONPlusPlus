
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

#ifndef _JSON_BOOLEAN_VALUE_H_
#define _JSON_BOOLEAN_VALUE_H_

namespace JSON {

class BooleanValue :
	public ValueT<BooleanType, BooleanDataType>
{
	friend class ValueFactory;

protected:
	BooleanValue() {m_Value = false;}

public:
	virtual ~BooleanValue() {}

	bool operator == (const BooleanValue& obj) const {return this->Equals(obj);}

	virtual BooleanType ToBoolean()	{return m_Value;}
	virtual IntegerType ToInteger()	{return (!m_Value ? 0 : 1);}
	virtual DoubleType ToDouble()	{return (!m_Value ? 0.0 : 1.0);}
	virtual StringType& ToString()	{return (!m_Value ? m_False : m_True);}

	virtual int Serialize(StringType& sf) const {sf = (!m_Value ? m_False : m_True); return 0;}
	virtual int Serialize(StringUTF8Type& sf) const {sf = (!m_Value ? m_False_UTF8 : m_True_UTF8); return 0;}
};

}

#endif //_JSON_BOOLEAN_VALUE_H_
