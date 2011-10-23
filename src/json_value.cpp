
#include "json.h"


namespace JSON {

StringType		Value::m_True(L"true"), Value::m_False(L"false"), Value::m_Null(L"null"), Value::m_CurrentPadding;
StringUTF8Type	Value::m_True_UTF8("true"), Value::m_False_UTF8("false"), Value::m_Null_UTF8("null"), Value::m_CurrentPadding_UTF8;
int				Value::m_CurrentDocLevel = 0;

const BooleanType	Value::m_NullBoolean(false);
const IntegerType	Value::m_NullInteger(0);
const DoubleType	Value::m_NullDouble(0.0);
const StringType	Value::m_NullString;
const DateTimeType	Value::m_NullDateTime;
const BinaryType	Value::m_NullBinary;
const ObjectType	Value::m_NullObject;
const ArrayType		Value::m_NullArray;


int Value::UnescapeStringInPlace(wchar_t * escaped_str, int *len)
{
	int i, r = 0;
	wchar_t *src_ptr, *end_ptr, *target_ptr, num[6];

	end_ptr = (target_ptr = src_ptr = escaped_str) + (*len);

	for (; src_ptr < end_ptr; ++src_ptr, ++target_ptr) {
		if (*src_ptr != L'\\') {*target_ptr = *src_ptr; continue;}

		++src_ptr;	//Skip the backslash

		switch (*src_ptr) {
		case L't':	*target_ptr = L'\t'; break;
		case L'n':	*target_ptr = L'\n'; break;
		case L'r':	*target_ptr = L'\r'; break;
		case L'b':	*target_ptr = L'\b'; break;
		case L'f':	*target_ptr = L'\f'; break;
		case L'\'':	*target_ptr = L'\''; break;
		case L'\"':	*target_ptr = L'\"'; break;
		case L'\\':	*target_ptr = L'\\'; break;
		case L'/':	*target_ptr = L'/'; break;
		
		case L'u':	// Escape Unicode character
			for (i=0; i < 4; ++i)
				if (!isxdigit(num[i] = *(++src_ptr)))
					goto done;
			num[i] = L'\0';
			
			*target_ptr = (wchar_t)wcstoul(num, NULL, 16);
			break;

		case L'0':	// Escape numeric sequence
			for (i=0; i < 3; ++i)
				if (!isdigit(num[i] = *(++src_ptr)))
					goto done;
			num[i] = L'\0';
			
			*target_ptr = (wchar_t)wcstoul(num, NULL, 8);
		}
	}
	
	done:
	*target_ptr = L'\0';

	*len = target_ptr - escaped_str;
	return (errno = 0);
}

int Value::UnescapeString(const wchar_t * escaped_str, int len, wchar_t **unescaped_str, int *unescaped_len)
{
	int r = 0;

	if (!(*unescaped_str = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1)))) return errno;
	*unescaped_len = len;

	memmove(*unescaped_str, escaped_str, sizeof(wchar_t) * len);
	if ((r = Value::UnescapeStringInPlace(*unescaped_str, unescaped_len))) goto done;

	*unescaped_str = (wchar_t *)realloc(*unescaped_str, sizeof(wchar_t) * (*unescaped_len + 1));

done:
	if (r) {
		free(*unescaped_str);
		*unescaped_str = NULL;
	}
	return (errno = r);
}

int Value::UnescapeString(const char * escaped_str, int len, wchar_t **unescaped_str, int *unescaped_len)
{
	int r;

	//Convert the string to Unicode before unescaping
	if ((r = UTF8::ToUnicode(escaped_str, len, unescaped_str, unescaped_len))) return r;
	if ((r = Value::UnescapeStringInPlace(*unescaped_str, unescaped_len))) {
		free(*unescaped_str); *unescaped_str = NULL;
		return r;
	}
	*unescaped_str = (wchar_t *)realloc(*unescaped_str, sizeof(wchar_t) * (*unescaped_len + 1));

	return (errno = r);
}

}
