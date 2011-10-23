
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

int Document::Load(Value** doc_root, ParsingError &parsing_error, const char* filename, bool buffered_mode)
{
	IFileInputSource *input_source = buffered_mode ? (IFileInputSource *)(new BufferedFileInputSource) : (IFileInputSource *)(new FileInputSource);
	if (!input_source) return errno;
	int r = input_source->Set(filename);
	if (r) {delete input_source; return (errno = r);}
	return this->Parse(doc_root, parsing_error, *input_source);
}

}
