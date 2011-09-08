
#ifndef _UTF_8_H_
#define _UTF_8_H_

#include <clocale>
#include <string>

namespace JSON {


class UTF8
{
protected:
#if !defined(WIN32) && !defined(_WINDOWS_)
	static _locale_t m_UTF8_locale;
#endif

public:
	static int ToUnicode(const char *utf8_data, int len, wchar_t **wstr, int *wlen);
	static int ToUnicode(const char *utf8_data, int len, wchar_t *wstr, int *wlen);
	static int ToUnicode(const char *utf8_data, int len, std::wstring& str);
	static int FromUnicode(const wchar_t *wstr, int wlen, char *str, int *len);
	static int FromUnicode(const wchar_t *wstr, int wlen, char **str, int *len);
	static int FromUnicode(const std::wstring& wstr, char **str, int *len);
};

}

#endif
