
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

#ifndef _JSON_DOCUMENT_H_
#define _JSON_DOCUMENT_H_


namespace JSON {

class ParsingError
{
protected:
	char			*m_message;
	ScanLocation	m_location;

public:
	ParsingError() : m_message(NULL) {}
	virtual ~ParsingError() {if (m_message != NULL) free(m_message);}

	void Set(const json_parsing_result& r)
	{
		m_message = r.error_message;
		m_location.line = r.error_location_line;
		m_location.column = r.error_location_column;
	}

	const char *ErrorMessage() {return m_message;}
	ScanLocation ParsingLocation() {return m_location;}
};

class Document
{
public:
	virtual ~Document() {}

	///< Parse a UTF-8 character string
	int Parse(Value** doc_root, ParsingError &parsing_error, const char* contents, int length=-1);
	
	///< Parse a Unicode character string
	int Parse(Value** doc_root, ParsingError &parsing_error, StringType& contents);

	int Parse(Value** doc_root, ParsingError &parsing_error, IInputSource& input_source);

	int Load(Value** doc_root, ParsingError &parsing_error, const char* filename, bool buffered_mode=true);
	int Persist(const Value& doc_root, const char* filename) const;

	Value *Create() {return ValueFactory::CreateObject();}
};

}

#endif
