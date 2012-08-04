
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

#ifndef _JSON_INPUT_SOURCE_H_
#define _JSON_INPUT_SOURCE_H_


namespace JSON {

class IInputSource
{
public:
	virtual ~IInputSource() {}

	virtual int Read(char *buffer, size_t size) = 0;
	virtual bool EndOfInput() = 0;
};

class IFileInputSource :
	public IInputSource
{
public:
	virtual ~IFileInputSource() {}

	virtual int Set(const char *filename) = 0;
};


class StringInputSource :
	public IInputSource
{
protected:
	int		m_length, m_position;
	char	*m_string;

public:
	StringInputSource() : m_string(NULL), m_length(0), m_position(0) {}
	virtual ~StringInputSource();

	int Set(char *str, int length=-1, bool take_ownership=false);
	int Set(wchar_t *str, int length=-1);

	virtual int Read(char *buffer, size_t size);
	virtual bool EndOfInput();
};


class FileInputSource :
	public IFileInputSource
{
protected:
	int m_fd;
	bool m_own_fd;

public:
	FileInputSource() : m_fd(-1), m_own_fd(false) {}
	virtual ~FileInputSource() {this->Set(-1);}

	virtual int Set(const char *filename);
	int Set(int fd, bool take_ownership=false);

	virtual int Read(char *buffer, size_t size);
	virtual bool EndOfInput();
};

class BufferedFileInputSource :
	public IFileInputSource
{
protected:
	FILE *m_fp;
	bool m_own_fp;

public:
	BufferedFileInputSource() : m_fp(NULL), m_own_fp(false) {}
	virtual ~BufferedFileInputSource() {this->Set(NULL, false);}

	virtual int Set(const char *filename);
	int Set(FILE *fp, bool take_ownership);

	virtual int Read(char *buffer, size_t size);
	virtual bool EndOfInput();
};

}

#endif
