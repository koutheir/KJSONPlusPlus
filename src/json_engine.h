
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

#include <stdint.h>
#include <stdio.h>
#include <malloc.h>

#include "os_spec.h"

#ifndef _JSON_ENGINE_H_
#define _JSON_ENGINE_H_


//We don't need "yyinput" for the moment
#define YY_NO_INPUT

#define YYMALLOC malloc
#define YYFREE free

#ifdef __cplusplus
extern "C" {
#endif

// Get the needed symbols and declarations for the parser
#include "json_parser.h"

//Declare prototypes of some mandatory functions defined in the scanner and
//parser-generated code.

typedef struct json_parsing_result_ {
	void	*value;
	char	*error_message;
	size_t	error_location_line, error_location_column;
} json_parsing_result;

int yylex();
void yyerror(json_parsing_result *parsing_result, const char *error_desc);
void yyrestart(FILE *input_file);
int yyparse(json_parsing_result *parsing_result);

//Delcare prototypes of functions used by the scanner and the parser to generate the
//in-memory representation of the JSON data parsed.

void json_unescape_string(wchar_t **wstr, int *wlen, const char * str, int len);

void * json_create_null_value();
void * json_create_boolean_value(int value);
void * json_create_integer_value(long long value);
void * json_create_double_value(double value);
void * json_create_string_value(wchar_t * value, int length, int take_ownership);
void * json_create_datetime_value(wchar_t * value, int length, int take_ownership);
void * json_create_binary_value(wchar_t * value, int length, int take_ownership);

void * json_create_empty_object_value();
void * json_append_to_object_value(void * object, wchar_t * name, int name_length, void * value, int take_name_ownership, int destroy_object_if_fails);

void * json_create_empty_array_value();
void * json_append_to_array_value(void * array, void * value, int destroy_array_if_fails);

#ifdef __cplusplus
}
#endif

#endif
