
#include "json.h"
#include "os_spec.h"


//Report the syntactic error
void yyerror(json_parsing_result *parsing_result, const char *error_desc)
{
	if (parsing_result->error_message != NULL) free(parsing_result->error_message);
	parsing_result->error_message = strdup(error_desc);

	const JSON::ScanLocation loc = JSON::Scanner::SingletonScanner().CurrentState().location;
	parsing_result->error_location_line = loc.line;
	parsing_result->error_location_column = loc.column;
}

//This converts the string into Unicode then unescapes it
void json_unescape_string(wchar_t **wstr, int *wlen, const char * str, int len)
{
	JSON::Value::UnescapeString(str, len, wstr, wlen);
}

void * json_create_null_value()
{
	return JSON::ValueFactory::Create(JSON::NullDataType);
}

void * json_create_boolean_value(int value)
{
	return JSON::ValueFactory::Create(JSON::BooleanDataType, &value);
}

void * json_create_integer_value(long long value)
{
	return JSON::ValueFactory::Create(JSON::IntegerDataType, &value);
}

void * json_create_double_value(double value)
{
	return JSON::ValueFactory::Create(JSON::DoubleDataType, &value);
}

void * json_create_string_value(wchar_t * value, int length, int take_ownership)
{
	JSON::StringType value_w(value, length);
	if (take_ownership) free(value);
	return JSON::ValueFactory::Create(JSON::StringDataType, &value_w);
}

void * json_create_datetime_value(wchar_t * value, int length, int take_ownership)
{
	JSON::DateTimeType tv;
	JSON::ISO8601::FromString(tv, value, length);
	if (take_ownership) free(value);
	return JSON::ValueFactory::Create(JSON::DateTimeDataType, &tv);
}

void * json_create_binary_value(wchar_t * value, int length, int take_ownership)
{
	JSON::Base85::Decoder dec;
	JSON::BinaryType data;
	dec.Decode(value, length, data);
	if (take_ownership) free(value);
	return JSON::ValueFactory::Create(JSON::BinaryDataType, &data);
}

void * json_create_empty_object_value()
{
	return JSON::ValueFactory::Create(JSON::ObjectDataType);
}

void * json_append_to_object_value(void * object, wchar_t * name, int name_length, void * value, int take_name_ownership, int destroy_object_if_fails)
{
	JSON::StringType name_w(name, name_length);
	if (take_name_ownership) free(name);

	int r = ((JSON::ObjectValue *)object)->Add(name_w, *(JSON::Value *)value);
	if (!r) return object;

	if (destroy_object_if_fails) {
		delete (JSON::Value *)value;
		delete (JSON::ObjectValue *)object;
	}
	return NULL;
}

void * json_create_empty_array_value()
{
	return JSON::ValueFactory::Create(JSON::ArrayDataType);
}

void * json_append_to_array_value(void * array, void * value, int destroy_array_if_fails)
{
	int r = 0;
	try {
		((JSON::ArrayValue *)array)->ToArray().push_back((JSON::Value *)value);
	} catch (...) {r = ENOMEM;}
	if (!r) return array;

	if (destroy_array_if_fails) {
		delete (JSON::Value *)value;
		delete (JSON::ArrayValue *)array;
	}
	return NULL;
}
