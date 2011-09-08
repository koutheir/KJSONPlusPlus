
#include "utf8.h"

#if defined(WIN32) || defined(_WINDOWS_)
#include <windows.h>
#endif

namespace JSON {

#if !defined(WIN32) && !defined(_WINDOWS_)
_locale_t UTF8::m_UTF8_locale = NULL;
#endif

int UTF8::ToUnicode(const char *utf8_data, int len, wchar_t *wstr, int *wlen)
{
#if defined(WIN32) || defined(_WINDOWS_)
	len = MultiByteToWideChar(CP_UTF8, 0, utf8_data, len, wstr, len * 4);
#else
	if (!m_UTF8_locale) m_UTF8_locale = _create_locale(LC_ALL, "en_US.UTF-8");
	len = mbstowcs_l(wstr, utf8_data, len, m_UTF8_locale);
#endif

	if (wlen != NULL) *wlen = len;
	return (errno = 0);
}

int UTF8::ToUnicode(const char *utf8_data, int len, wchar_t **wstr, int *wlen)
{
	if (len == -1) len = strlen(utf8_data);
	if (!(*wstr = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1) * 4))) return errno;
	
	int wlen_;
	int r = UTF8::ToUnicode(utf8_data, len, *wstr, &wlen_);
	if (r) {free(*wstr); return r;}

	*wstr = (wchar_t *)realloc(*wstr, sizeof(wchar_t) * (wlen_ + 1));
	if (wlen != NULL) *wlen = wlen_;
	return (errno = 0);
}

int UTF8::ToUnicode(const char *utf8_data, int len, std::wstring& str)
{
	int wlen = (len + 1) * 4;
	str.resize(wlen, L'\0');

	int r = UTF8::ToUnicode(utf8_data, len, (wchar_t *)str.c_str(), &wlen);
	if (r) return r;

	str.resize(wlen, L'\0');
	return (errno = 0);
}

int UTF8::FromUnicode(const wchar_t *wstr, int wlen, char *str, int *len)
{
#if defined(WIN32) || defined(_WINDOWS_)
	wlen = WideCharToMultiByte(CP_UTF8, 0, wstr, wlen, str, wlen * 4, NULL, NULL);
#else
	if (!m_UTF8_locale) m_UTF8_locale = _create_locale(LC_ALL, "en_US.UTF-8");
	wlen = wcstombs_l(str, wstr, wlen, m_UTF8_locale);
#endif

	if (len != NULL) *len = wlen;
	return (errno = 0);
}

int UTF8::FromUnicode(const wchar_t *wstr, int wlen, char **str, int *len)
{
	int len_ = (wlen + 1) * 4;
	*str = (char *)malloc(sizeof(char) * len_);
	if (!*str) return NULL;

	int r = UTF8::FromUnicode(wstr, wlen, *str, &len_);
	if (r) {free(*str); return r;}

	*str = (char *)realloc(*str, sizeof(char) * (len_ + 1));
	if (len != NULL) *len = len_;
	return (errno = 0);
}

int UTF8::FromUnicode(const std::wstring& wstr, char **str, int *len)
{
	return UTF8::FromUnicode(wstr.c_str(), wstr.length(), str, len);
}

}
