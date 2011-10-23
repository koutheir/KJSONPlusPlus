
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
