
#ifndef _JSON_BOOLEAN_VALUE_H_
#define _JSON_BOOLEAN_VALUE_H_

namespace JSON {

class BooleanValue :
	public ValueT<BooleanType, BooleanDataType>
{
	friend class ValueFactory;

protected:
	BooleanValue() {m_Value = false;}

public:
	virtual ~BooleanValue() {}

	bool operator == (const BooleanValue& obj) const {return this->Equals(obj);}

	virtual BooleanType ToBoolean()	{return m_Value;}
	virtual IntegerType ToInteger()	{return (!m_Value ? 0 : 1);}
	virtual DoubleType ToDouble()	{return (!m_Value ? 0.0 : 1.0);}
	virtual StringType& ToString()	{return (!m_Value ? m_False : m_True);}

	virtual int Serialize(StringType& sf) const {sf = (!m_Value ? m_False : m_True); return 0;}
	virtual int Serialize(StringUTF8Type& sf) const {sf = (!m_Value ? m_False_UTF8 : m_True_UTF8); return 0;}
};

}

#endif //_JSON_BOOLEAN_VALUE_H_
