
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
