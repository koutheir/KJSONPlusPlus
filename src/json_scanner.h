
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

	ScanLocation() : line(1), column(1) {}

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

public:
	YYCTYPE			*cursor, *limit, *marker, *token;
	ScanLocation	location;

public:
	ScannerState(IInputSource& input_source, bool take_ownership=false);
	virtual ~ScannerState();

	void ExpandBuffer(int additional_count);
};


class Scanner
{
protected:	
	ScannerState	*m_current_state;
	static Scanner	*m_singleton_scanner;

public:
	Scanner() : m_current_state(NULL) {}
	
	int InitializeScan(ScannerState& state);
	int ScanNextLexem();
	void EndScan();
	
	static Scanner& SingletonScanner() {return *m_singleton_scanner;}
	const ScannerState& CurrentState() {return *m_current_state;}
};

};

#endif
