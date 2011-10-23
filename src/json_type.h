
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

#ifndef _JSON_TYPE_H_
#define _JSON_TYPE_H_

#include <string>
#include <vector>
#include <map>

namespace JSON {

///All defined JSON types
enum DataType {
	NullDataType = 1,	///< null
	BooleanDataType,	///< true or false
	IntegerDataType,	///< int
	DoubleDataType,		///< double
	StringDataType,		///< " string-contents "
	DateTimeDataType,	///< "YYYY-MM-DDThh:mm:ss.frZ" i.e. "2010-06-08T14:26:23.56Z"
	BinaryDataType,		///< binary data encoded in Base85 format
	ObjectDataType,		///< { list-of-pairs }
	ArrayDataType		///< [ list-of-values ]
};

class Value;

///Mapping of JSON types to C++ objects
typedef bool							BooleanType;	///< JSON boolean type mapped to C++ type
typedef long long						IntegerType;	///< JSON integer type mapped to C++ type
typedef double							DoubleType;		///< JSON double type mapped to C++ type
typedef std::wstring					StringType;		///< JSON string type mapped to C++ type
typedef std::string						StringUTF8Type;	///< JSON UTF-8 string type mapped to C++ type
typedef struct tm						DateTimeType;	///< JSON date/time type mapped to C++ type (Extension to the standard)
typedef JSON::Buffer					BinaryType;		///< JSON binary type mapped to C++ type (Extension to the standard)
typedef std::pair<StringType, Value *>	PairType;		///< JSON pair type mapped to C++ type
typedef std::map<StringType, Value *>	ObjectType;		///< JSON object type mapped to C++ type
typedef std::vector<Value *>			ArrayType;		///< JSON array type mapped to C++ type

}

#endif
