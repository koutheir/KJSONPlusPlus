
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

	virtual int Add(DataType type, const StringType& key);
	virtual int Add(const StringType& key, BooleanType value);
	virtual int Add(const StringType& key, IntegerType value);
	virtual int Add(const StringType& key, DoubleType value);
	virtual int Add(const StringType& key, const StringType& value);
	virtual int Add(const StringType& key, const DateTimeType& value);
	virtual int Add(const StringType& key, const BinaryType& value);
	virtual int Add(const StringType& key, const ObjectType& value);
	virtual int Add(const StringType& key, const ArrayType& value);
	virtual int Add(const StringType& key, Value& contents);
	virtual int Remove(const StringType& key);
	virtual Value* GetChild(const StringType& key, bool AbsentReturnsNull=false);
};

}

#endif //_JSON_OBJECT_VALUE_H_
