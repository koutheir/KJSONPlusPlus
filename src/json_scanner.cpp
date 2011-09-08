
#include "json.h"

namespace JSON {

ScannerState::ScannerState(IInputSource& input_source, bool take_ownership) :
	m_input_source_owned(take_ownership), m_input_source(&input_source), m_buffer_size(0), m_buffer(NULL)
{
}

ScannerState::~ScannerState()
{
	if (m_input_source_owned && m_input_source != NULL) delete m_input_source;
	free(m_buffer);
}

void ScannerState::ExpandBuffer(int additional_count)
{
}

int Scanner::InitializeScan(ScannerState& state)
{
}

void Scanner::EndScan()
{
}

}
