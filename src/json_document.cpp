
#include "json.h"
#include <sys/stat.h>
#include <fcntl.h>


namespace JSON {

int Document::Parse(Value** doc_root, ParsingError &parsing_error, IInputSource& input_source)
{
	ScannerState *scanner_state = new ScannerState(input_source, true);
	int r = Scanner::SingletonScanner().InitializeScan(*scanner_state);
	if (r) {delete scanner_state; return (errno = r);}

	json_parsing_result result;
	memset(&result, 0, sizeof(json_parsing_result));
	r = (!yyparse(&result) ? 0 : EINVAL);

	*doc_root = (JSON::Value *)result.value;
	parsing_error.Set(result);

	Scanner::SingletonScanner().EndScan();

	return (errno = r);
}

int Document::Parse(Value** doc_root, ParsingError &parsing_error, StringType& contents)
{
	StringInputSource *input_source = new StringInputSource;
	int r = input_source->Set((wchar_t *)contents.c_str(), contents.length());
	if (r) {delete input_source; return (errno = r);}

	return this->Parse(doc_root, parsing_error, *input_source);
}

int Document::Parse(Value** doc_root, ParsingError &parsing_error, const char* contents, int length)
{
	StringInputSource *input_source = new StringInputSource;
	int r = input_source->Set((char *)contents, length, false);
	if (r) {delete input_source; return (errno = r);}

	return this->Parse(doc_root, parsing_error, *input_source);
}

int Document::Persist(const Value& doc_root, const char* filename) const
{
	//Opens an empty file for writing. If the given file exists, it is truncated.
	int fd = open(filename, O_WRONLY, 0);
	if (fd == -1) return errno;

	StringUTF8Type sf;
	int r = doc_root.Serialize(sf);
	if (r != 0) {close(fd); return r;}

	write(fd, sf.c_str(), sf.length());
	close(fd);
	return r;
}

int Document::Load(Value** doc_root, ParsingError &parsing_error, const char* filename)
{
	FileInputSource *input_source = new FileInputSource;
	int r = input_source->Set(filename);
	if (r) {delete input_source; return (errno = r);}

	return this->Parse(doc_root, parsing_error, *input_source);
}

}
