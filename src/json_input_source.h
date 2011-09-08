
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
	public IInputSource
{
protected:
	int m_fd;
	bool m_own_fd;

public:
	FileInputSource() : m_fd(-1), m_own_fd(false) {}
	virtual ~FileInputSource() {this->Set(-1);}

	int Set(const char *filename);
	int Set(int fd, bool take_ownership=false);

	virtual int Read(char *buffer, size_t size);
	virtual bool EndOfInput();
};

}

#endif
