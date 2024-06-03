#include "str.h"
#include <string.h>
#include <stdlib.h>

Str* str_from_cstr(const char* string)
{
	Str* s = malloc(sizeof(*s));
	s->size = strlen(string);
	s->str = malloc(s->size + 1);
	memcpy(s->str, string, s->size + 1);
	return s;
}

Str* str_from_char(char ch)
{
	Str* s = malloc(sizeof(*s));
	s->size = 1;
	s->str = malloc(s->size + 1);
	memcpy(s->str, &ch, s->size);
	s->str[1] = '\0';
	return s;
}
