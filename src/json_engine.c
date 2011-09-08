
#include "json_engine.h"

/*
	When the scanner receives an end-of-file indication from YY_INPUT, it then
	checks the yywrap() function:
	- If yywrap() returns false (zero), then it is assumed that the function
		has gone ahead and set up yyin to point to another input file, and
		scanning continues.
	- If it returns true (non-zero), then the scanner terminates, returning 0
		to its caller.

	Note that in either case, the start condition remains unchanged; it does
	not revert to INITIAL. 
*/
int yywrap()
{
	return 1;
}
