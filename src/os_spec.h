
#if defined(WIN32) || defined(_WINDOWS_)

#include <io.h>

#define snwprintf	_snwprintf
#define snprintf	_snprintf
#define strcasecmp	_stricmp
#define wcscasecmp	_wcsicmp
#define wcstoll		_wcstoi64
#define strtoll		_strtoi64
/*
#define wasctime	_wasctime
#define stat		_stat
#define fileno		_fileno
#define strdup		_strdup
#define open		_open
#define close		_close
#define eof			_eof
#define read		_read
*/
#else

#include <unistd.h>

#endif
