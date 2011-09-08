
#ifndef _JSON_ARRAY_VALUE_H_
#define _JSON_ARRAY_VALUE_H_

namespace JSON {

class ArrayValue :
	public ValueT<ArrayType, ArrayDataType>
{
	friend class ValueFactory;

protected:
	ArrayValue() {}

public:
	virtual ~ArrayValue();

	bool operator == (const ArrayValue& obj) const {return this->Equals(obj);}

	virtual int Set(const void *value);

	virtual ArrayType& ToArray()	{return m_Value;}
	virtual StringType& ToString()	{static StringType s; this->Serialize(s); return s;}

	virtual int Serialize(StringType& sf) const;
	virtual int Serialize(StringUTF8Type& sf) const;
};

}

#endif //_JSON_ARRAY_VALUE_H_
