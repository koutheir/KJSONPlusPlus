
#include "json.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <fcntl.h>
#include <sys/types.h>


namespace JSON {

StringInputSource::~StringInputSource()
{
	free(m_string);
	m_string = NULL;
	m_position = m_length = 0;
}

int StringInputSource::Set(char *str, int length, bool take_ownership)
{
	m_length = (length == -1) ? strlen(str) : length;
	if (take_ownership)
		m_string = str;
	else {
		if (!(m_string = (char *)malloc(m_length + 1))) return errno;
		memcpy(m_string, str, m_length);
		m_string[m_length] = '\0';
	}
	return (errno = 0);
}

int StringInputSource::Set(wchar_t *str, int length)
{
	return UTF8::FromUnicode((const wchar_t *)str, length, &m_string, &m_length);
}

int StringInputSource::Read(char *buffer, size_t size)
{
	if (!size) return 0;	// Nothing to read

	size_t remaining_size = m_length - m_position;
	if (!remaining_size) return 0;	// End Of Input

	size_t size_to_read = (size > remaining_size) ? remaining_size : size;
	memmove(buffer, m_string + m_position, size_to_read);

	m_position += size_to_read;
	return size_to_read;
}

bool StringInputSource::EndOfInput()
{
	return (m_length <= m_position);
}

int FileInputSource::Set(const char *filename)
{
	return this->Set(open(filename, O_RDONLY|O_BINARY, 0), true);
}

int FileInputSource::Set(int fd, bool take_ownership)
{
	if (m_own_fd && m_fd != -1) close(m_fd);

	m_fd = fd;
	m_own_fd = take_ownership;
	return (errno = 0);
}

int FileInputSource::Read(char *buffer, size_t size)
{
	return read(m_fd, buffer, size);
}

bool FileInputSource::EndOfInput()
{
	return (eof(m_fd) != 0);
}

}
