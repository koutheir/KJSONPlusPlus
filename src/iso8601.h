
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

#ifndef _ISO_8601_H_
#define _ISO_8601_H_

#include <string>

namespace JSON {


class ISO8601
{
protected:
	template<class T> static int ParseTime(const T* str, int len, const T** end_ptr, int *hour, int *minute, int *second, int *second_fraction);
	template<class T> static int ParseDate(const T* str, int len, const T** end_ptr, int *year, int *month, int *day, int *hour, int *minute, int *second, int *second_fraction);
	template<class T> static int ParseDate(const T* str, int len, const T** end_ptr, struct tm& value);

public:
	static int ToString(const struct tm& value, wchar_t *wstr, int *wlen);
	static int ToString(const struct tm& value, char *str, int *len);
	static int ToString(const struct tm& value, wchar_t **wstr, int *wlen);
	static int ToString(const struct tm& value, char **str, int *len);
	static int ToString(const struct tm& value, std::string& str);
	static int ToString(const struct tm& value, std::wstring& str);

	static int FromString(struct tm& value, const wchar_t *wstr, int wlen);
	static int FromString(struct tm& value, const char *str, int len);
	static int FromString(struct tm& value, const std::string& str);
	static int FromString(struct tm& value, const std::wstring& str);
};

}

#endif
