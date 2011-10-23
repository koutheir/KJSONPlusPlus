
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


int yylex()
{
	return JSON::Scanner::SingletonScanner().ScanNextLexem();
}


namespace JSON {
	
const size_t ScannerState::m_init_buffer_size = 5;
Scanner	Scanner::m_singleton_scanner;


ScannerState::ScannerState(IInputSource& input_source, bool take_ownership, size_t LocationLine, size_t LocationColumn) :
	m_input_source_owned(take_ownership), m_input_source(&input_source), m_buffer_size(0), m_buffer(NULL),
	cursor(NULL), limit(NULL), marker(NULL), token(NULL), location(LocationLine, LocationColumn)
{
}

ScannerState::~ScannerState()
{
	if (m_input_source_owned && m_input_source != NULL) delete m_input_source;
	free(m_buffer);
}

int ScannerState::Initialize()
{
	if (!(m_buffer = (YYCTYPE *)malloc(sizeof(YYCTYPE) * m_init_buffer_size))) return errno;
	m_buffer_size = m_init_buffer_size;
	m_buffer[m_buffer_size - 1] = NULL;

	cursor = limit = token = marker = m_buffer;
	return (errno = 0);
}

int ScannerState::ExpandBuffer(int additional_count)
{
	int available_count_for_token = limit - token;
	int token_offset = token - m_buffer;

	if ((size_t)(available_count_for_token + additional_count) >= m_buffer_size) {
		//Enlarge the buffer
		size_t new_size = available_count_for_token + additional_count + m_init_buffer_size + 1;
        YYCTYPE* new_buffer = (YYCTYPE *)realloc(m_buffer, sizeof(YYCTYPE) * new_size);
		if (!new_buffer) return errno;
        m_buffer_size = new_size;

		//Update scanner pointers
		if (new_buffer != m_buffer) {
			cursor = new_buffer + (cursor - m_buffer);
			token = new_buffer + (token - m_buffer);
			limit = new_buffer + (limit - m_buffer);
			marker = new_buffer + (marker - m_buffer);

			m_buffer = new_buffer;
		}
	}
	
	if ((available_count_for_token > 0) && (m_buffer != token)) {
		//Translate back buffer contents to discard already scanned data
		//and allow more buffer space to be used by the scanner.
		memmove(m_buffer, token, available_count_for_token * sizeof(YYCTYPE));
	}

	//Read more data into the buffer
	int read_count = m_input_source->Read(m_buffer + available_count_for_token, additional_count);
	m_buffer[available_count_for_token + read_count] = NULL;

	//Update scanner pointers
    token = m_buffer;
    cursor -= token_offset;
    marker -= token_offset;
    limit += (read_count - token_offset);

	return (errno = 0);
}

int Scanner::InitializeScan(ScannerState& state)
{
	m_current_state = &state;
	return m_current_state->Initialize();
}

void Scanner::EndScan()
{
	if (m_current_state != NULL) {delete m_current_state; m_current_state = NULL;}
}

}
