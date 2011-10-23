
/*
Copyright 2011-2011 Koutheir Attouchi. All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE FREEBSD PROJECT ``AS IS'' AND ANY EXPRESS OR
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
