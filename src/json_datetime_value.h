
#ifndef _JSON_DATE_TIME_VALUE_H_
#define _JSON_DATE_TIME_VALUE_H_

#include <memory.h>

inline bool operator == (const JSON::DateTimeType& v1, const JSON::DateTimeType& v2)
{
	return (memcmp(&v1, &v2, sizeof(v1)) == 0);
}

namespace JSON {

class DateTimeValue :
	public ValueT<DateTimeType, DateTimeDataType>
{
	friend class ValueFactory;

protected:
	DateTimeValue() {memset(&m_Value, 0, sizeof(m_Value));}

public:
	virtual ~DateTimeValue() {}

	bool operator == (const DateTimeValue& obj) const {return this->Equals(obj);}

	virtual DateTimeType& ToDateTime()	{return m_Value;}
	virtual StringType& ToString()		{static StringType s; ISO8601::ToString(m_Value, s); return s;}

	virtual int Serialize(StringType& sf) const
	{
		int r = ISO8601::ToString(m_Value, sf);
		sf.insert(0, 1, L'\"');
		sf += L'\"';
		return (errno = r);
	}
	virtual int Serialize(StringUTF8Type& sf) const
	{
		int r = ISO8601::ToString(m_Value, sf);
		sf.insert(0, 1, '\"');
		sf += '\"';
		return (errno = r);
	}
};

}

#endif //_JSON_DATE_TIME_VALUE_H_
