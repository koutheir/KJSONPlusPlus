
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

#ifndef _JSON_STRING_VALUE_H_
#define _JSON_STRING_VALUE_H_

namespace JSON {

class StringValue :
	public ValueT<StringType, StringDataType>
{
	friend class ValueFactory;

protected:
	StringValue() {}

public:
	virtual ~StringValue() {}

	bool operator == (const StringValue& obj) const {return this->Equals(obj);}

	virtual StringType& ToString()	{return m_Value;}
	virtual BooleanType ToBoolean();
	virtual IntegerType ToInteger();
	virtual DoubleType ToDouble();
	virtual DateTimeType& ToDateTime();

	template<class T> int SerializeT(std::basic_string<T, std::char_traits<T>, std::allocator<T> >& sf) const;
	virtual int Serialize(StringType& sf) const;
	virtual int Serialize(StringUTF8Type& sf) const;
};

}

#endif //_JSON_STRING_VALUE_H_
