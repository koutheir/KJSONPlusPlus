
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

NullValue *ValueFactory::m_NullSingleton = NULL;


Value *ValueFactory::Create(DataType obj_type, const void *init_data)
{
	Value *p;
	int r;

	switch (obj_type) {
	case NullDataType:
		if (!m_NullSingleton) {
			if (!(m_NullSingleton = new NullValue)) {
				errno = ENOMEM;
				return NULL;
			}
		}
		p = m_NullSingleton;
		break;

	case BooleanDataType:	p = new BooleanValue;	break;
	case IntegerDataType:	p = new IntegerValue;	break;
	case DoubleDataType:	p = new DoubleValue;	break;
	case StringDataType:	p = new StringValue;	break;
	case DateTimeDataType:	p = new DateTimeValue;	break;
	case BinaryDataType:	p = new BinaryValue;	break;
	case ObjectDataType:	p = new ObjectValue;	break;
	case ArrayDataType:		p = new ArrayValue;		break;
	default:				errno = EINVAL; p = NULL;
	}
	if (!p) return NULL;

	r = p->Initialize();
	if (r) {
		delete p;
		errno = r;
		return NULL;
	}

	//Initialize created object if required and possible
	if (init_data != NULL) {
		r = p->Set(init_data);
		if (r) {	//Initialization failed. Abort all.
			delete p;
			errno = r;
			return NULL;
		}
	}

	errno = r;
	return p;
}

NullValue* ValueFactory::CreateNull() {return static_cast<NullValue *>(ValueFactory::Create(NullDataType));}
BooleanValue* ValueFactory::CreateBoolean(BooleanType init_data) {return static_cast<BooleanValue *>(ValueFactory::Create(BooleanDataType, &init_data));}
IntegerValue* ValueFactory::CreateInteger(IntegerType init_data) {return static_cast<IntegerValue *>(ValueFactory::Create(IntegerDataType, &init_data));}
DoubleValue* ValueFactory::CreateDouble(DoubleType init_data) {return static_cast<DoubleValue *>(ValueFactory::Create(DoubleDataType, &init_data));}
StringValue* ValueFactory::CreateString(const StringType& init_data) {return static_cast<StringValue *>(ValueFactory::Create(StringDataType, &init_data));}
DateTimeValue* ValueFactory::CreateDateTime(const DateTimeType& init_data) {return static_cast<DateTimeValue *>(ValueFactory::Create(DateTimeDataType, &init_data));}
BinaryValue* ValueFactory::CreateBinary(const BinaryType& init_data) {return static_cast<BinaryValue *>(ValueFactory::Create(BinaryDataType, &init_data));}
ObjectValue* ValueFactory::CreateObject() {return static_cast<ObjectValue *>(ValueFactory::Create(ObjectDataType));}
ArrayValue* ValueFactory::CreateArray() {return static_cast<ArrayValue *>(ValueFactory::Create(ArrayDataType));}

}
