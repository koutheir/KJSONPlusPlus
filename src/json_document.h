
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

	int Load(Value** doc_root, ParsingError &parsing_error, const char* filename);
	int Persist(const Value& doc_root, const char* filename) const;

	Value *Create() {return ValueFactory::CreateObject();}
};

}

#endif
