#include "str.h"
#include <string.h>
#include <stdlib.h>

string* str_from_cstr(const char* str)
{
	string* s = malloc(sizeof(*s));
	s->size = strlen(str);
	s->str = malloc(s->size + 1);
	memcpy(s->str, str, s->size + 1);
	return s;
}

string* str_from_char(char ch)
{
	string* s = malloc(sizeof(*s));
	s->size = 1;
	s->str = malloc(s->size + 1);
	memcpy(s->str, &ch, s->size);
	s->str[1] = '\0';
	return s;
}
