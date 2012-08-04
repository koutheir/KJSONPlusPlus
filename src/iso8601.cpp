
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

#include "iso8601.h"
#include <errno.h>
#include <time.h>

#include "os_spec.h"


#define MAX_DATETIME_LENGTH		32

namespace JSON {

template<class T> int str_to_int(const T * str, int len, const T ** end_ptr, int base);

template<> inline int str_to_int(const char * str, int len, const char ** end_ptr, int base)
{
	// WARNING: len parameter is ignored for the moment. This is acceptable in the current module.
	return strtoul(str, (char **)end_ptr, base);
}

template<> inline int str_to_int(const wchar_t * str, int len, const wchar_t ** end_ptr, int base)
{
	// WARNING: len parameter is ignored for the moment. This is acceptable in the current module.
	return wcstoul(str, (wchar_t **)end_ptr, base);
}

template<class T> int is_digit(T c);
template<> inline int is_digit(wchar_t c) {return iswdigit(c);}
template<> inline int is_digit(char c) {return isdigit(c);}

template<class T>
int ISO8601::ParseTime(const T* str, int len, const T** end_ptr, int *hour, int *minute, int *second, int *second_fraction)
{
	int r = 0;	//Nothing parsed
	const T *pEnd = str, *pStop = str + len;

	if (end_ptr != NULL) *end_ptr = str;

	if (!hour) return r;
	*hour = str_to_int<T>(str, pStop - str, &pEnd, 10);
	if (pEnd == str) return r;
	r++;	//hour parsed
	if (end_ptr != NULL) *end_ptr = pEnd;
	if (pEnd >= pStop) return r;
	if (*pEnd != ':') return r;

	if (!minute) return r;
	str = ++pEnd;
	if (str >= pStop) return r;
	*minute = str_to_int<T>(str, pStop - str, &pEnd, 10);
	if (pEnd == str) return r;
	r++;	//minute parsed
	if (end_ptr != NULL) *end_ptr = pEnd;
	if (pEnd >= pStop) return r;
	if (*pEnd != ':') return r;

	if (!second) return r;
	str = ++pEnd;
	if (str >= pStop) return r;
	*second = str_to_int<T>(str, pStop - str, &pEnd, 10);
	if (pEnd == str) return r;
	r++;	//second parsed
	if (end_ptr != NULL) *end_ptr = pEnd;
	if (pEnd >= pStop) return r;
	if (*pEnd != '.' && *pEnd != ',') return r;

	if (!second_fraction) return r;
	str = ++pEnd;
	if (str >= pStop) return r;
	*second_fraction = str_to_int<T>(str, pStop - str, &pEnd, 10);
	if (pEnd == str) return r;
	r++;	//second_fraction parsed
	if (end_ptr != NULL) *end_ptr = pEnd;
	return r;
}

template<class T>
int ISO8601::ParseDate(const T* str, int len, const T** end_ptr, int *year, int *month, int *day, int *hour, int *minute, int *second, int *second_fraction)
{
	if (!is_digit<T>(*str)) return EINVAL;

	//2010-06-08T14:26:23.56Z
	int r = EINVAL;
	const T* pStart = str, *pEnd = str, *pStop = str + len;

	if (*pEnd == 'T') goto ParseTimeLabel;

	*year = str_to_int<T>(str, pStop - str, &pEnd, 10);
	if (pEnd == str) goto OnDone;
	if (*pEnd == 'T') goto ParseTimeLabel;
	if (*pEnd == 'Z') goto ParseDone;
	if (*pEnd != '-') goto OnDone;

	str = ++pEnd;
	*month = str_to_int<T>(str, pStop - str, &pEnd, 10);
	if (pEnd == str) goto OnDone;
	if (*pEnd == 'T') goto ParseTimeLabel;
	if (*pEnd == 'Z') goto ParseDone;
	if (*pEnd != '-') goto OnDone;

	str = ++pEnd;
	*day = str_to_int<T>(str, pStop - str, &pEnd, 10);
	if (pEnd == str) goto OnDone;
	if (*pEnd == 'T') goto ParseTimeLabel;
	if (*pEnd == 'Z') goto ParseDone;
	goto OnDone;

	ParseTimeLabel:
	str = ++pEnd;
	if (!ISO8601::ParseTime<T>(str, pStop - str, &pEnd, hour, minute, second, second_fraction)) goto OnDone;
	if (*pEnd != 'Z') goto OnDone;

	ParseDone:
	if (end_ptr != NULL) *end_ptr = ++pEnd;
	r = 0;

	OnDone:
	return r;
}

template<class T>
int ISO8601::ParseDate(const T* str, int len, const T** end_ptr, struct tm& value)
{
	int second_fraction=0;		//unused in "struct tm"

	memset(&value, 0, sizeof(struct tm));
	value.tm_isdst = -1;	//Auto Determine whether daylight saving time is in effect
	value.tm_wday = value.tm_yday = -1;

	int r = ISO8601::ParseDate<T>(str, len, end_ptr, &value.tm_year, &value.tm_mon, &value.tm_mday, &value.tm_hour, &value.tm_min, &value.tm_sec, &second_fraction);
	value.tm_year -= 1900;	//Number of years since 1900
	value.tm_mon --;	//Between 0 and 11

	mktime(&value);
	return (errno = r);
}

int ISO8601::ToString(const struct tm& value, wchar_t *wstr, int *wlen)
{
	//2010-06-08T14:26:23Z
	*wlen = snwprintf(wstr, *wlen, L"%.4d-%.2d-%.2dT%.2d:%.2d:%.2dZ", (1900 + value.tm_year), (1 + value.tm_mon), value.tm_mday, value.tm_hour, value.tm_min, value.tm_sec);
	return (errno = 0);
}

int ISO8601::ToString(const struct tm& value, char *str, int *len)
{
	//2010-06-08T14:26:23Z
	*len = snprintf(str, *len, "%.4d-%.2d-%.2dT%.2d:%.2d:%.2dZ", (1900 + value.tm_year), (1 + value.tm_mon), value.tm_mday, value.tm_hour, value.tm_min, value.tm_sec);
	return (errno = 0);
}

int ISO8601::ToString(const struct tm& value, wchar_t **wstr, int *wlen)
{
	if (!(*wstr = (wchar_t *)malloc(sizeof(wchar_t) * (*wlen = MAX_DATETIME_LENGTH)))) return errno;
	return ISO8601::ToString(value, *wstr, wlen);
}

int ISO8601::ToString(const struct tm& value, char **str, int *len)
{
	if (!(*str = (char *)malloc(sizeof(char) * (*len = MAX_DATETIME_LENGTH)))) return errno;
	return ISO8601::ToString(value, *str, len);
}

int ISO8601::ToString(const struct tm& value, std::string& str)
{
	int len = MAX_DATETIME_LENGTH;
	str.resize(len, '\0');
	int r = ISO8601::ToString(value, const_cast<char *>(str.c_str()), &len);
	str.resize(len);
	return (errno = r);
}

int ISO8601::ToString(const struct tm& value, std::wstring& str)
{
	int len = MAX_DATETIME_LENGTH;
	str.resize(len, '\0');
	int r = ISO8601::ToString(value, const_cast<wchar_t *>(str.c_str()), &len);
	str.resize(len);
	return (errno = r);
}

int ISO8601::FromString(struct tm& value, const wchar_t *wstr, int wlen)
{
	return ISO8601::ParseDate<wchar_t>(wstr, wlen, NULL, value);
}

int ISO8601::FromString(struct tm& value, const char *str, int len)
{
	return ISO8601::ParseDate<char>(str, len, NULL, value);
}

int ISO8601::FromString(struct tm& value, const std::string& str)
{
	return ISO8601::FromString(value, str.c_str(), str.length());
}

int ISO8601::FromString(struct tm& value, const std::wstring& str)
{
	return ISO8601::FromString(value, str.c_str(), str.length());
}

}
