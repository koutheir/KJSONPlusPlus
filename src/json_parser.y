%{
#include "json_engine.h"
%}

%error-verbose
%parse-param{json_parsing_result *parsing_result}

%union {
	void *		value;
	long long	number_int;
	double		number_double;

	struct {
		int		length;
		wchar_t	*data;
	} string;
}

%token json_null json_false json_true
%token <string> json_string json_datetime
%token <number_double> json_double_number
%token <number_int> json_integer_number

%type <value> json_data json_value json_array_list json_object_list

%start json_data

%%

json_data:
	/* Empty */
	{
		$$ = 0;
		YYACCEPT;
	}

	| json_value
	{
		$$ = $1;
		parsing_result->value = $1;
		YYACCEPT;
	}
	;

json_value:
	json_null					{$$ = json_create_null_value();}
	| json_false				{$$ = json_create_boolean_value(0);}
	| json_true					{$$ = json_create_boolean_value(1);}
	| json_integer_number		{$$ = json_create_integer_value($1);}
	| json_double_number		{$$ = json_create_double_value($1);}
	| json_datetime				{$$ = json_create_datetime_value($1.data, $1.length, 1);}
	| json_string				{$$ = json_create_string_value($1.data, $1.length, 1);}
	| '{' '}'					{$$ = json_create_empty_object_value();}
	| '{' json_object_list '}'	{$$ = $2;}
	| '[' ']'					{$$ = json_create_empty_array_value();}
	| '[' json_array_list ']'	{$$ = $2;}
	;

json_object_list:
	json_string ':' json_value
	{$$ = json_append_to_object_value(json_create_empty_object_value(), $1.data, $1.length, $3, 1, 1);}
	
	| json_object_list ',' json_string ':' json_value
	{$$ = json_append_to_object_value($1, $3.data, $3.length, $5, 1, 1);}
	;

json_array_list:
	json_value
	{$$ = json_append_to_array_value(json_create_empty_array_value(), $1, 1);}
	
	| json_array_list ',' json_value
	{$$ = json_append_to_array_value($1, $3, 1);}
	;

%%
