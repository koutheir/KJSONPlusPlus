
/*
Copyright 2011-2011 Koutheir Attouchi. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY KOUTHEIR ATTOUCHI ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL KOUTHEIR ATTOUCHI OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of Koutheir Attouchi.
*/

#ifndef _JSON_VALUE_H_
#define _JSON_VALUE_H_

namespace JSON {

class Value;


#define DECLARE_ADD_METHOD(type)	\
	virtual int Add(const StringType& key, type##Type contents, bool overwrite = false)			{return EINVAL;}

#define DECLARE_ADD_METHOD_REF(type)	\
	virtual int Add(const StringType& key, const type##Type& contents, bool overwrite = false)	{return EINVAL;}

class Object
{
public:
	virtual int Add(DataType type, const StringType& key, bool overwrite = false)	{return EINVAL;}
	virtual int Add(const StringType& key, Value& contents, bool overwrite = false)	{return EINVAL;}

	DECLARE_ADD_METHOD(Boolean);
	DECLARE_ADD_METHOD(Integer);
	DECLARE_ADD_METHOD(Double);
	DECLARE_ADD_METHOD_REF(DateTime);
	DECLARE_ADD_METHOD_REF(Binary);
	DECLARE_ADD_METHOD_REF(String);
	DECLARE_ADD_METHOD_REF(Object);
	DECLARE_ADD_METHOD_REF(Array);

	virtual int Remove(const StringType& key)	{return EINVAL;}

	virtual StringType* ChildKey(const StringType& key)											{return NULL;}
	virtual const StringType* ChildKey(const StringType& key) const								{return const_cast<Object *>(this)->ChildKey(key);}

	virtual Value* GetChild(const StringType& key, bool AbsentReturnsNull=false)				{return NULL;}
	virtual const Value* GetChild(const StringType& key, bool AbsentReturnsNull=false) const	{return const_cast<Object *>(this)->GetChild(key, AbsentReturnsNull);}

	virtual Value& operator [] (const StringType& key)					{return *this->GetChild(key, true);}
	virtual const Value& operator [] (const StringType& key) const		{return *const_cast<Object *>(dynamic_cast<const Object *>(this))->GetChild(key, true);}

	virtual Value& operator [] (const wchar_t* key)						{return *this->GetChild(StringType(key), true);}
	virtual const Value& operator [] (const wchar_t* key) const			{return *const_cast<Object *>(dynamic_cast<const Object *>(this))->GetChild(StringType(key), true);}

	virtual StringType& operator () (const StringType& key)				{return *this->ChildKey(key);}
	virtual const StringType& operator () (const StringType& key) const	{return *const_cast<Object *>(dynamic_cast<const Object *>(this))->ChildKey(key);}

	virtual StringType& operator () (const wchar_t* key)				{return *this->ChildKey(StringType(key));}
	virtual const StringType& operator () (const wchar_t* key) const	{return *const_cast<Object *>(dynamic_cast<const Object *>(this))->ChildKey(StringType(key));}
};

#undef DECLARE_ADD_METHOD
#undef DECLARE_ADD_METHOD_REF


class Array
{
public:
	virtual int Add(Value& contents)	{return EINVAL;}

	virtual int Remove(int index)		{return EINVAL;}

	virtual Value* GetChild(int index)				{return NULL;}
	virtual const Value* GetChild(int index) const	{return const_cast<Array *>(this)->GetChild(index);}

	virtual Value& operator [] (int index)					{return *this->GetChild(index);}
	virtual const Value& operator [] (int index) const		{return *const_cast<Array *>(dynamic_cast<const Array *>(this))->GetChild(index);}

	virtual Array& operator += (Value& contents) {this->Add(contents); return (*this);}
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
	public Object,
	public Array
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

	template <class T>
	static int EscapeString(const StringType& unescaped_str, std::basic_string<T, std::char_traits<T>, std::allocator<T> >& escaped_str);

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

#undef DECLARE_NULL_BUFFER
#undef DECLARE_TO_TYPE_ACCESSORS
#undef DECLARE_TO_TYPE_ACCESSORS_REF


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


template <>
inline static char Value::HexToChar(int x)
{
	return (x >= 0 && x <= 9) ? (x + '0') : ((x >= 10 && x <= 15) ? (x - 10 + 'a') : '?');
}

template <>
inline static wchar_t Value::HexToChar(int x)
{
	return (x >= 0 && x <= 9) ? (x + L'0') : ((x >= 10 && x <= 15) ? (x - 10 + L'a') : L'?');
}

template <class T>
int Value::EscapeString(const wchar_t * unescaped_str, int len, T **escaped_str, int *escaped_len)
{
	T *target_ptr;
	const wchar_t *src_ptr, *end_ptr;

	end_ptr = (src_ptr = unescaped_str) + len;

	//Allocating enough space for escaped string
	if (!(*escaped_str = (T *)malloc(*escaped_len = (sizeof(T) * (len * 6 + 1))))) return errno;

	for (target_ptr = *escaped_str; src_ptr < end_ptr; ++src_ptr, ++target_ptr) {
		switch (*src_ptr) {
		case L'\t':	*(target_ptr++) = (T)'\\'; *target_ptr = (T)'t'; break;
		case L'\n':	*(target_ptr++) = (T)'\\'; *target_ptr = (T)'n'; break;
		case L'\r':	*(target_ptr++) = (T)'\\'; *target_ptr = (T)'r'; break;
		case L'\b':	*(target_ptr++) = (T)'\\'; *target_ptr = (T)'b'; break;
		case L'\f':	*(target_ptr++) = (T)'\\'; *target_ptr = (T)'f'; break;
		case L'\'':	*(target_ptr++) = (T)'\\'; *target_ptr = (T)'\''; break;
		case L'\"':	*(target_ptr++) = (T)'\\'; *target_ptr = (T)'\"'; break;
		case L'\\':	*(target_ptr++) = (T)'\\'; *target_ptr = (T)'\\'; break;
		case L'/':	*(target_ptr++) = (T)'\\'; *target_ptr = (T)'/'; break;
		default:
			if (*src_ptr < L' ' || *src_ptr > L'~') {
				*(target_ptr++)	= (T)'\\';
				*(target_ptr++)	= (T)'u';
				*(target_ptr++)	= Value::HexToChar<T>((*src_ptr >> 12) & 0xF);
				*(target_ptr++)	= Value::HexToChar<T>((*src_ptr >> 8) & 0xF);
				*(target_ptr++)	= Value::HexToChar<T>((*src_ptr >> 4) & 0xF);
				*target_ptr		= Value::HexToChar<T>(*src_ptr & 0xF);
			} else
				*target_ptr = (T)(*src_ptr & 0xFF);
		}
	}

	*target_ptr = L'\0';
	*escaped_len = target_ptr - (*escaped_str);
	*escaped_str = (T *)realloc(*escaped_str, sizeof(T) * (*escaped_len + 1));
	return (errno = 0);
}

template <class T>
int Value::EscapeString(const StringType& unescaped_str, std::basic_string<T, std::char_traits<T>, std::allocator<T> >& escaped_str)
{
	int r;
	T *_escaped_str;
	int _escaped_len;

	if ((r = Value::EscapeString(unescaped_str.c_str(), unescaped_str.length(), &_escaped_str, &_escaped_len))) return r;
	escaped_str.assign(_escaped_str, _escaped_len);
	free(_escaped_str);

	return (errno = 0);
}

}

#endif //_JSON_VALUE_H_
