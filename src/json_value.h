
#ifndef _JSON_VALUE_H_
#define _JSON_VALUE_H_

namespace JSON {

class Value;

class Object
{
public:
	virtual int Add(DataType type, const StringType& key)					{return EINVAL;}
	virtual int Add(const StringType& key, BooleanType contents)			{return EINVAL;}
	virtual int Add(const StringType& key, IntegerType contents)			{return EINVAL;}
	virtual int Add(const StringType& key, DoubleType contents)				{return EINVAL;}
	virtual int Add(const StringType& key, const DateTimeType& contents)	{return EINVAL;}
	virtual int Add(const StringType& key, const BinaryType& contents)		{return EINVAL;}
	virtual int Add(const StringType& key, const StringType& contents)		{return EINVAL;}
	virtual int Add(const StringType& key, const ObjectType& contents)		{return EINVAL;}
	virtual int Add(const StringType& key, const ArrayType& contents)		{return EINVAL;}
	virtual int Add(const StringType& key, Value& contents)					{return EINVAL;}

	virtual int Remove(const StringType& key)								{return EINVAL;}

	virtual Value* GetChild(const StringType& key, bool AbsentReturnsNull=false)				{return NULL;}
	virtual const Value* GetChild(const StringType& key, bool AbsentReturnsNull=false) const	{return const_cast<Object *>(this)->GetChild(key, AbsentReturnsNull);}

	virtual Value& operator [] (const StringType& key)				{return *this->GetChild(key, true);}
	virtual const Value& operator [] (const StringType& key) const	{return *const_cast<Object *>(dynamic_cast<const Object *>(this))->GetChild(key, true);}

	virtual Value& operator [] (const wchar_t* key)				{return *this->GetChild(StringType(key), true);}
	virtual const Value& operator [] (const wchar_t* key) const	{return *const_cast<Object *>(dynamic_cast<const Object *>(this))->GetChild(StringType(key), true);}
};


#define DECLARE_NULL_BUFFER(type)	\
	static const type##Type	m_Null##type

#define DECLARE_TO_TYPE_ACCESSORS_REF(type)	\
	virtual type##Type& To##type()				{return const_cast<type##Type&>(m_Null##type);}	\
	virtual const type##Type& To##type() const	{return const_cast<Value *>(this)->To##type();}

#define DECLARE_TO_TYPE_ACCESSORS(type)	\
	virtual type##Type To##type()				{return const_cast<type##Type&>(m_Null##type);}	\
	virtual const type##Type To##type() const	{return const_cast<Value *>(this)->To##type();}

class Value :
	public Object
{
	friend class ValueFactory;

public:
	static StringType		m_True, m_False, m_Null, m_CurrentPadding;
	static StringUTF8Type	m_True_UTF8, m_False_UTF8, m_Null_UTF8, m_CurrentPadding_UTF8;
	static int				m_CurrentDocLevel;

	DECLARE_NULL_BUFFER(Boolean);
	DECLARE_NULL_BUFFER(Integer);
	DECLARE_NULL_BUFFER(Double);
	DECLARE_NULL_BUFFER(DateTime);
	DECLARE_NULL_BUFFER(Binary);
	DECLARE_NULL_BUFFER(String);
	DECLARE_NULL_BUFFER(Object);
	DECLARE_NULL_BUFFER(Array);

protected:	//Normal construction is prohibited, use ValueFactory
	Value() {}
	virtual int Initialize() {return 0;}

public:
	virtual ~Value() {}

	template <class T>
	static T HexToChar(int x);

	static int UnescapeStringInPlace(wchar_t * escaped_str, int *len);
	static int UnescapeString(const wchar_t * escaped_str, int len, wchar_t **unescaped_str, int *unescaped_len);
	static int UnescapeString(const char * escaped_str, int len, wchar_t **unescaped_str, int *unescaped_len);

	template <class T>
	static int EscapeString(const wchar_t * unescaped_str, int len, T **escaped_str, int *escaped_len);

	static int EscapeString(const StringType& unescaped_str, StringType& escaped_str);
	static int EscapeString(const StringType& unescaped_str, StringUTF8Type& escaped_str);

	virtual bool Equals(const Value& /* obj */) const {return false;}	///< Generic type data is "always different"

	virtual DataType Type() const {return NullDataType;}	///< One way to identify the object type without C++ RTTI

	///Value reading using generic pointers
	/**
	\param value Buffer where to put a pointer to the value.
	*/
	virtual int Get(void ** value) {return ENOENT;}

	///Value writing using generic pointers
	/**
	\param value Pointer to the value.
	*/
	virtual int Set(const void * value) {return ENOENT;}


	///Value to escaped string conversion
	/**
	\return	The string returned is meant to be safely converted to UTF-8 and
	transferred as a JSON-conforming textual data.
	*/
	virtual int Serialize(StringType& sf) const {sf = m_Null; return 0;}

	virtual int Serialize(StringUTF8Type& sf) const {sf = m_Null_UTF8; return 0;}

	DECLARE_TO_TYPE_ACCESSORS(Boolean);
	DECLARE_TO_TYPE_ACCESSORS(Integer);
	DECLARE_TO_TYPE_ACCESSORS(Double);
	DECLARE_TO_TYPE_ACCESSORS_REF(DateTime);
	DECLARE_TO_TYPE_ACCESSORS_REF(Binary);
	DECLARE_TO_TYPE_ACCESSORS_REF(String);
	DECLARE_TO_TYPE_ACCESSORS_REF(Object);
	DECLARE_TO_TYPE_ACCESSORS_REF(Array);
};


template<class T, enum DataType TypeID>
class ValueT :
	public Value
{
protected:
	T	m_Value;

protected:
	ValueT() {}

public:
	virtual ~ValueT() {}

	bool operator == (const ValueT<T, TypeID>& obj) const {return this->Equals(obj);}

	virtual bool Equals(const Value& obj) const
	{
		if (obj.Type() != TypeID) return false;
		return static_cast<const ValueT<T, TypeID>&>(obj).m_Value == m_Value;
	}

	virtual DataType Type() const {return TypeID;}

	virtual int Get(void **value)		{*value = &m_Value; return 0;}
	virtual int Set(const void *value)	{m_Value = *static_cast<const T *>(value); return 0;}
};

}

#endif //_JSON_VALUE_H_
