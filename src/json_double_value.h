
#ifndef _JSON_DOUBLE_VALUE_H_
#define _JSON_DOUBLE_VALUE_H_

namespace JSON {

class DoubleValue :
	public ValueT<DoubleType, DoubleDataType>
{
	friend class ValueFactory;

protected:
	DoubleValue() {m_Value = 0.0;}

public:
	virtual ~DoubleValue() {}

	bool operator == (const DoubleValue& obj) const {return this->Equals(obj);}

	virtual DoubleType ToDouble()	{return m_Value;}
	virtual IntegerType ToInteger()	{return (IntegerType)m_Value;}
	virtual BooleanType ToBoolean()	{return (m_Value != 0.0);}
	virtual StringType& ToString()	{static StringType s; this->Serialize(s); return s;}

	virtual int Serialize(StringType& sf) const
	{
		sf.resize(128, L'\0');
		sf.resize(snwprintf(const_cast<wchar_t *>(sf.c_str()), sf.capacity(), L"%f", m_Value));
		return 0;
	}

	virtual int Serialize(StringUTF8Type& sf) const
	{
		sf.resize(128, '\0');
		sf.resize(snprintf(const_cast<char *>(sf.c_str()), sf.capacity(), "%f", m_Value));
		return 0;
	}
};

}

#endif //_JSON_DOUBLE_VALUE_H_
