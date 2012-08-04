
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

#ifndef _JSON_SCANNER_H_
#define _JSON_SCANNER_H_

#include "json_input_source.h"


#define YYCTYPE		char
#define YYCURSOR	m_current_state->cursor
#define YYLIMIT		m_current_state->limit
#define YYMARKER	m_current_state->marker
#define YYTOKEN		m_current_state->token
#define YYFILL(n)	m_current_state->ExpandBuffer(n)
#define yyleng		(YYCURSOR - YYTOKEN)


namespace JSON {

struct ScanLocation
{
	size_t	line, column;

	ScanLocation(size_t Line=1, size_t Column=1) : line(Line), column(Column) {}

	void Reset() {line = column = 1;}
	void NewLine() {++line; column = 0;}
};

class ScannerState
{
protected:
	bool			m_input_source_owned;
	IInputSource	*m_input_source;
	size_t			m_buffer_size;
	YYCTYPE			*m_buffer;

	static const size_t	m_init_buffer_size;

public:
	YYCTYPE			*cursor, *limit, *marker, *token;
	ScanLocation	location;

public:
	ScannerState(IInputSource& input_source, bool take_ownership=false, size_t LocationLine=1, size_t LocationColumn=1);
	virtual ~ScannerState();

	int Initialize();
	int ExpandBuffer(int additional_count);
};


class Scanner
{
protected:	
	ScannerState	*m_current_state;
	static Scanner	m_singleton_scanner;

public:
	Scanner() : m_current_state(NULL) {}
	
	int InitializeScan(ScannerState& state);
	int ScanNextLexem();
	void EndScan();
	
	static Scanner& SingletonScanner() {return m_singleton_scanner;}
	const ScannerState& CurrentState() {return *m_current_state;}
};

};

#endif
