
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

int BufferedFileInputSource::Set(const char *filename)
{
	return this->Set(fopen(filename, "rb"), true);
}

int BufferedFileInputSource::Set(FILE *fp, bool take_ownership)
{
	if (m_own_fp && m_fp != NULL) fclose(m_fp);

	m_fp = fp;
	m_own_fp = take_ownership;
	return (errno = 0);
}

int BufferedFileInputSource::Read(char *buffer, size_t size)
{
	return fread(buffer, 1, size, m_fp);
}

bool BufferedFileInputSource::EndOfInput()
{
	return (feof(m_fp) != 0);
}

}
