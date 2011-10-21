
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
	virtual DateTimeType ToDateTime();

	template<class T> int SerializeT(std::basic_string<T, std::char_traits<T>, std::allocator<T> >& sf) const;
	virtual int Serialize(StringType& sf) const;
	virtual int Serialize(StringUTF8Type& sf) const;
};

}

#endif //_JSON_STRING_VALUE_H_
