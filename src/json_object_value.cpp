
#include "json.h"


#define IMPLEMENT_ADD_METHOD_BODY(type)	\
{	\
	Value *obj = ValueFactory::Create(type##DataType, &contents);	\
	if (!obj) return errno;			\
	int r = this->Add(key, *obj);	\
	if (r) delete obj;				\
	return (errno = r);				\
}

#define IMPLEMENT_ADD_METHOD(type)	\
int ObjectValue::Add(const StringType& key, type##Type contents)	\
IMPLEMENT_ADD_METHOD_BODY(type)

#define IMPLEMENT_ADD_METHOD_REF(type)	\
int ObjectValue::Add(const StringType& key, const type##Type& contents)	\
IMPLEMENT_ADD_METHOD_BODY(type)


namespace JSON {

ObjectValue::~ObjectValue()
{
	for (ObjectType::iterator i = m_Value.begin(); i != m_Value.end(); ++i) delete i->second;
	m_Value.clear();
}

int ObjectValue::Set(const void *value)
{
	//Remove the old data
	for (ObjectType::iterator i = m_Value.begin(); i != m_Value.end(); ++i) delete i->second;
	m_Value.clear();

	//Copy the new data to this instance
	int r = 0;
	const ObjectType *pObject = static_cast<const ObjectType *>(value);
	for (ObjectType::const_iterator i = pObject->begin(); i != pObject->end(); ++i) {
		if (!m_Value.insert(PairType(i->first, i->second)).second) {
			r = EEXIST;
			break;
		}
	}
	return r;
}

int ObjectValue::Serialize(StringType& sf) const
{
	StringType str(L"{\n");
	ENTER_LEVEL();

	int r = 0;
	StringType ts;
	
	for (ObjectType::const_iterator i = m_Value.begin(); i != m_Value.end(); ++i) {
		this->EscapeString(i->first, ts);

		str += m_CurrentPadding;
		str += L'\"';
		str += ts;
		str += L"\":";

		r = i->second->Serialize(ts);
		if (r) return r;

		str += ts;
		str += L",\n";
	}

	if (m_Value.size() > 0) {
		str.erase(str.size() - 2, 1);

		LEAVE_LEVEL();
		str += m_CurrentPadding;

		str += L'}';
	} else {
		LEAVE_LEVEL();

		str[1] = L'}';
	}

	sf = str;
	return r;
}

int ObjectValue::Serialize(StringUTF8Type& sf) const
{
	StringUTF8Type str("{\n");
	ENTER_LEVEL();

	int r = 0;
	StringUTF8Type ts;
	
	for (ObjectType::const_iterator i = m_Value.begin(); i != m_Value.end(); ++i) {
		this->EscapeString(i->first, ts);

		str += m_CurrentPadding_UTF8;
		str += '\"';
		str += ts;
		str += "\":";

		r = i->second->Serialize(ts);
		if (r) return r;

		str += ts;
		str += ",\n";
	}

	if (m_Value.size() > 0) {
		str.erase(str.size() - 2, 1);

		LEAVE_LEVEL();
		str += m_CurrentPadding_UTF8;

		str += '}';
	} else {
		LEAVE_LEVEL();

		str[1] = '}';
	}

	sf = str;
	return r;
}

int ObjectValue::Add(const StringType& key, Value& contents)
{
	return (m_Value.insert(PairType(key, &contents)).second ? 0 : EEXIST);
}

int ObjectValue::Add(DataType type, const StringType& key)
{
	Value *obj = ValueFactory::Create(type);
	if (!obj) return errno;
	int r = this->Add(key, *obj);
	if (r) delete obj;
	return (errno = r);
}

IMPLEMENT_ADD_METHOD(Boolean);
IMPLEMENT_ADD_METHOD(Integer);
IMPLEMENT_ADD_METHOD(Double);
IMPLEMENT_ADD_METHOD_REF(String);
IMPLEMENT_ADD_METHOD_REF(Object);
IMPLEMENT_ADD_METHOD_REF(Array);

int ObjectValue::Remove(const StringType& key)
{
	ObjectType::iterator i = m_Value.find(key);
	if (i == m_Value.end()) return 0;

	delete i->second;
	m_Value.erase(i);
	return 0;
}

Value* ObjectValue::GetChild(const StringType& key, bool AbsentReturnsNull)
{
	ObjectType::iterator i = m_Value.find(key);
	if (i == m_Value.end()) {
		if (AbsentReturnsNull) return ValueFactory::CreateNull();
		return NULL;
	}
	return i->second;
}

}
