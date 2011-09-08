
#include "json.h"

namespace JSON {

ArrayValue::~ArrayValue()
{
	for (ArrayType::iterator i = m_Value.begin(); i != m_Value.end(); ++i) delete (*i);
	m_Value.clear();
}

int ArrayValue::Set(const void *value)
{
	//Remove the old data
	for (ArrayType::iterator i = m_Value.begin(); i != m_Value.end(); ++i) delete (*i);
	m_Value.clear();

	//Copy the new data to this instance
	const ArrayType *pArray = static_cast<const ArrayType *>(value);
	m_Value.insert(m_Value.begin(), pArray->begin(), pArray->end());
	return 0;
}

int ArrayValue::Serialize(StringType& sf) const
{
	StringType str(L"[\n");
	ENTER_LEVEL();

	StringType ts;
	int r = 0;
	int j=0, count = m_Value.size();
	for (ArrayType::const_iterator i = m_Value.begin(); i != m_Value.end(); ++i, ++j) {
		str += m_CurrentPadding;

		r = (**i).Serialize(ts);
		if (r) return r;

		str += ts;

		if (j < (count-1))	str += L",\n";
		else				str += L'\n';
	}

	LEAVE_LEVEL();
	if (m_Value.size() > 0) {
		str += m_CurrentPadding;
		str += L']';
	} else {
		str[1] = L']';
	}

	sf = str;
	return r;
}

int ArrayValue::Serialize(StringUTF8Type& sf) const
{
	StringUTF8Type str("[\n");
	ENTER_LEVEL();

	StringUTF8Type ts;
	int r = 0;
	int j=0, count = m_Value.size();
	for (ArrayType::const_iterator i = m_Value.begin(); i != m_Value.end(); ++i, ++j) {
		str += m_CurrentPadding_UTF8;

		r = (**i).Serialize(ts);
		if (r) return r;

		str += ts;

		if (j < (count-1))	str += ",\n";
		else				str += '\n';
	}

	LEAVE_LEVEL();
	if (m_Value.size() > 0) {
		str += m_CurrentPadding_UTF8;
		str += ']';
	} else {
		str[1] = ']';
	}

	sf = str;
	return r;
}

}
