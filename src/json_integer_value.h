
#ifndef _JSON_INTEGER_VALUE_H_
#define _JSON_INTEGER_VALUE_H_

namespace JSON {

class IntegerValue :
	public ValueT<IntegerType, IntegerDataType>
{
	friend class ValueFactory;

protected:
	IntegerValue() {m_Value = 0;}

public:
	virtual ~IntegerValue() {}

	bool operator == (const IntegerValue& obj) const {return this->Equals(obj);}

	virtual IntegerType ToInteger()	{return m_Value;}
	virtual DoubleType ToDouble()	{return (DoubleType)m_Value;}
	virtual BooleanType ToBoolean()	{return (m_Value != 0.0);}
	virtual StringType& ToString()	{static StringType s; this->Serialize(s); return s;}

	virtual int Serialize(StringType& sf) const
	{
		sf.resize(128, L'\0');
		sf.resize(snwprintf(const_cast<wchar_t *>(sf.c_str()), sf.capacity(), L"%I64i", m_Value));
		return 0;
	}

	virtual int Serialize(StringUTF8Type& sf) const
	{
		sf.resize(128, '\0');
		sf.resize(snprintf(const_cast<char *>(sf.c_str()), sf.capacity(), "%I64i", m_Value));
		return 0;
	}
};

}

#endif //_JSON_INTEGER_VALUE_H_
