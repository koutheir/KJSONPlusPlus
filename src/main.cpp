
#include <iostream>

#include "json.h"

using namespace std;

int main()
{
	int r;
	JSON::Document doc;
	JSON::Value *value;
	std::string str;
	JSON::ParsingError perr;

	r = doc.Load(&value, perr, "test.json");

/*	const char *data = "{\"one\":\"hello_\\u03bb_\\u03a8_KOUTHEIR_\\0101TTOUCHI\"\r\n,\n \"two\":\n[-22, 0,  [{}]]}";

	cout << data << endl;

	r = doc.Parse(&value, perr, data);
*/
	if (r)
		cerr << "Line " << perr.ParsingLocation().line << ", Column " << perr.ParsingLocation().column << " : " << perr.ErrorMessage() << endl;
	else {
		value->Serialize(str);

		cout << str << endl;

//		delete value;
	}

	auto i = (*value).ToObject().begin();
	for (; i != (*value).ToObject().end(); i++)
		wcout << (*i).first << " : " << (*i).second->Type() << endl;
}
