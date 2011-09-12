/* Generated by re2c 0.13.5 */
#line 1 ".\\src\\json_scanner.re2c"

#include "json.h"

int JSON::Scanner::ScanNextLexem()
{
	YYCTYPE at_cursor;

	#line 18 ".\\src\\json_scanner.re2c"


	for (;;) {
		m_current_state->location.column += (YYCURSOR - YYTOKEN);
		YYTOKEN = YYCURSOR;
		
		
#line 19 ".\\src\\json_scanner.re2c.cpp"
{
	YYCTYPE yych;
	unsigned int yyaccept = 0;

	if ((YYLIMIT - YYCURSOR) < 5) YYFILL(5);
	yych = *YYCURSOR;
	switch (yych) {
	case '\t':
	case '\r':
	case ' ':	goto yy4;
	case '\n':	goto yy2;
	case '"':	goto yy10;
	case '+':
	case '-':	goto yy6;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy8;
	case 'f':	goto yy12;
	case 'n':	goto yy11;
	case 't':	goto yy13;
	default:	goto yy14;
	}
yy2:
	++YYCURSOR;
#line 27 ".\\\\src\\\\json_scanner.re2c"
	{
			m_current_state->location.NewLine();
			continue;	// Skip new line
		}
#line 56 ".\\src\\json_scanner.re2c.cpp"
yy4:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy46;
yy5:
#line 33 ".\\\\src\\\\json_scanner.re2c"
	{
			continue;	// Skip white space
		}
#line 66 ".\\src\\json_scanner.re2c.cpp"
yy6:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy36;
	default:	goto yy7;
	}
yy7:
#line 79 ".\\\\src\\\\json_scanner.re2c"
	{			
			return *YYTOKEN;
		}
#line 87 ".\\src\\json_scanner.re2c.cpp"
yy8:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case '.':	goto yy38;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy36;
	default:	goto yy9;
	}
yy9:
#line 47 ".\\\\src\\\\json_scanner.re2c"
	{
			at_cursor = *YYCURSOR;
			*YYCURSOR = '\0';
			yylval.number_int = strtoll(YYTOKEN, NULL, 10);
			*YYCURSOR = at_cursor;
			return json_integer_number;
		}
#line 113 ".\\src\\json_scanner.re2c.cpp"
yy10:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	goto yy30;
yy11:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'u':	goto yy25;
	default:	goto yy7;
	}
yy12:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'a':	goto yy20;
	default:	goto yy7;
	}
yy13:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 'r':	goto yy15;
	default:	goto yy7;
	}
yy14:
	yych = *++YYCURSOR;
	goto yy7;
yy15:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'u':	goto yy17;
	default:	goto yy16;
	}
yy16:
	YYCURSOR = YYMARKER;
	switch (yyaccept) {
	case 0: 	goto yy7;
	case 1: 	goto yy34;
	case 2: 	goto yy40;
	}
yy17:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy18;
	default:	goto yy16;
	}
yy18:
	++YYCURSOR;
#line 74 ".\\\\src\\\\json_scanner.re2c"
	{			
			return json_true;
		}
#line 167 ".\\src\\json_scanner.re2c.cpp"
yy20:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'l':	goto yy21;
	default:	goto yy16;
	}
yy21:
	yych = *++YYCURSOR;
	switch (yych) {
	case 's':	goto yy22;
	default:	goto yy16;
	}
yy22:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy23;
	default:	goto yy16;
	}
yy23:
	++YYCURSOR;
#line 69 ".\\\\src\\\\json_scanner.re2c"
	{
			return json_false;
		}
#line 192 ".\\src\\json_scanner.re2c.cpp"
yy25:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'l':	goto yy26;
	default:	goto yy16;
	}
yy26:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'l':	goto yy27;
	default:	goto yy16;
	}
yy27:
	++YYCURSOR;
#line 65 ".\\\\src\\\\json_scanner.re2c"
	{
			return json_null;
		}
#line 211 ".\\src\\json_scanner.re2c.cpp"
yy29:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy30:
	switch (yych) {
	case '"':	goto yy33;
	case '\\':	goto yy31;
	default:	goto yy29;
	}
yy31:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case '"':	goto yy35;
	case '\\':	goto yy31;
	default:	goto yy29;
	}
yy33:
	++YYCURSOR;
yy34:
#line 56 ".\\\\src\\\\json_scanner.re2c"
	{
			at_cursor = *YYCURSOR;
			*YYCURSOR = '\0';
			json_unescape_string(&yylval.string.data, &yylval.string.length, YYTOKEN + 1, yyleng - 2);
			*YYCURSOR = at_cursor;
			return json_string;
		}
#line 242 ".\\src\\json_scanner.re2c.cpp"
yy35:
	yyaccept = 1;
	YYMARKER = ++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case '"':	goto yy33;
	case '\\':	goto yy31;
	default:	goto yy29;
	}
yy36:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case '.':	goto yy38;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy36;
	default:	goto yy9;
	}
yy38:
	yyaccept = 2;
	YYMARKER = ++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy38;
	case 'E':
	case 'e':	goto yy41;
	default:	goto yy40;
	}
yy40:
#line 38 ".\\\\src\\\\json_scanner.re2c"
	{
			at_cursor = *YYCURSOR;
			*YYCURSOR = '\0';
			yylval.number_double = strtod(YYTOKEN, NULL);
			*YYCURSOR = at_cursor;
			return json_double_number;
		}
#line 300 ".\\src\\json_scanner.re2c.cpp"
yy41:
	yych = *++YYCURSOR;
	switch (yych) {
	case '+':
	case '-':	goto yy42;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy43;
	default:	goto yy16;
	}
yy42:
	yych = *++YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy43;
	default:	goto yy16;
	}
yy43:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy43;
	default:	goto yy40;
	}
yy45:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy46:
	switch (yych) {
	case '\t':
	case '\r':
	case ' ':	goto yy45;
	default:	goto yy5;
	}
}
#line 83 ".\\src\\json_scanner.re2c"

	}
}
