
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

#ifndef _JSON_VALUE_FACTORY_H_
#define _JSON_VALUE_FACTORY_H_

namespace JSON {

class ValueFactory
{
protected:
	static NullValue	*m_NullSingleton;

public:
	virtual ~ValueFactory() {}

	///Creates a JSON value given its type and a possible initial value.
	/**
	The created object can be used through this interface or directly after casting
	it to the right class.

	\param obj_type The JSON type of the newly created object.
	\param init_data Pointer to the initial value assigned to the object. Can be NULL.
	\return An object of the specified \a obj_type and eventually initialized with
		 \a init_data.

	\remark
	If \a init_data is not NULL and the object initialization fails, then the
	method fails.
	*/
	static Value *Create(DataType obj_type, const void *init_data=NULL);

	static NullValue*		CreateNull();
	static BooleanValue*	CreateBoolean(BooleanType init_data=false);
	static IntegerValue*	CreateInteger(IntegerType init_data);
	static DoubleValue*		CreateDouble(DoubleType init_data=0.0);
	static DateTimeValue*	CreateDateTime(const DateTimeType& init_data);
	static BinaryValue*		CreateBinary(const BinaryType& init_data);
	static StringValue*		CreateString(const StringType& init_data);
	static ObjectValue*		CreateObject();
	static ArrayValue*		CreateArray();
};

}

#endif //_JSON_VALUE_FACTORY_H_
