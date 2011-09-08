
#include "json_engine.h"


void * json_create_null_value()
{
	return NULL;
}

void * json_create_boolean_value(int data)
{
	return NULL;
}

void * json_create_integer_value(int data)
{
	return NULL;
}

void * json_create_double_value(double data)
{
	return NULL;
}

void * json_create_string_value(char * data, int length, int take_ownership)
{
	return NULL;
}

void * json_create_empty_object_value()
{
	return NULL;
}

void * json_append_to_object_value(void * object, char * name, int name_length, void * value, int take_name_ownership, int destroy_object_if_fails)
{
	return NULL;
}

void * json_create_empty_array_value()
{
	return NULL;
}

void * json_append_to_array_value(void * array, void * value, int destroy_array_if_fails)
{
	return NULL;
}
