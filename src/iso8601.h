
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
