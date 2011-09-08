
#include "json.h"

namespace JSON {

BooleanType StringValue::ToBoolean()
{
	if (!wcscasecmp(m_Value.c_str(), m_False.c_str()) ||
		!wcscasecmp(m_Value.c_str(), L"0") ||
		!wcscasecmp(m_Value.c_str(), L"off") ||
		!wcscasecmp(m_Value.c_str(), L"no")) return false;

	if (!wcscasecmp(m_Value.c_str(), m_True.c_str()) ||
		!wcscasecmp(m_Value.c_str(), L"1") ||
		!wcscasecmp(m_Value.c_str(), L"on") ||
		!wcscasecmp(m_Value.c_str(), L"yes")) return true;

	return const_cast<BooleanType&>(m_NullBoolean);
}

IntegerType StringValue::ToInteger()
{
	wchar_t *p=NULL;
	return wcstoll(m_Value.c_str(), &p, 10);
}

DoubleType StringValue::ToDouble()
{
	wchar_t *p=NULL;
	return wcstod(m_Value.c_str(), &p);
}

template<class T>
int StringValue::SerializeT(std::basic_string<T, std::char_traits<T>, std::allocator<T> >& sf) const
{
	T *escaped_str;
	int len;

	this->EscapeString<T>(m_Value.c_str(), m_Value.length(), &escaped_str, &len);

	sf = (T)'\"';
	sf.append(escaped_str, len);
	sf += (T)'\"';

	free(escaped_str);
	return 0;
}

int StringValue::Serialize(StringType& sf) const
{
	return this->SerializeT<wchar_t>(sf);
}

int StringValue::Serialize(StringUTF8Type& sf) const
{
	return this->SerializeT<char>(sf);
}

}
