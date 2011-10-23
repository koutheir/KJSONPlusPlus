
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

#ifndef _JSON_OBJECT_VALUE_H_
#define _JSON_OBJECT_VALUE_H_

namespace JSON {

class ObjectValue :
	public ValueT<ObjectType, ObjectDataType>
{
	friend class ValueFactory;

protected:
	ObjectValue() {}

public:
	virtual ~ObjectValue();

	bool operator == (const ObjectValue& obj) const {return this->Equals(obj);}

	virtual int Set(const void *value);

	virtual ObjectType& ToObject()	{return m_Value;}
	virtual StringType& ToString()	{static StringType s; this->Serialize(s); return s;}

	virtual int Serialize(StringType& sf) const;
	virtual int Serialize(StringUTF8Type& sf) const;

	virtual int Add(DataType type, const StringType& key, bool overwrite = false);
	virtual int Add(const StringType& key, Value& contents, bool overwrite = false);
	virtual int Add(const StringType& key, BooleanType value, bool overwrite = false);
	virtual int Add(const StringType& key, IntegerType value, bool overwrite = false);
	virtual int Add(const StringType& key, DoubleType value, bool overwrite = false);
	virtual int Add(const StringType& key, const StringType& value, bool overwrite = false);
	virtual int Add(const StringType& key, const DateTimeType& value, bool overwrite = false);
	virtual int Add(const StringType& key, const BinaryType& value, bool overwrite = false);
	virtual int Add(const StringType& key, const ObjectType& value, bool overwrite = false);
	virtual int Add(const StringType& key, const ArrayType& value, bool overwrite = false);
	
	virtual int Remove(const StringType& key);

	virtual StringType* ChildKey(const StringType& key);
	virtual Value* GetChild(const StringType& key, bool AbsentReturnsNull=false);
};

}

#endif //_JSON_OBJECT_VALUE_H_
