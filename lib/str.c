#include "str.h"
#include "arena.h"
#include <string.h>
#include <stdlib.h>

Str* str_from_cstr(const char* string)
{
	Str* s = malloc(sizeof(*s));
	s->size = strlen(string);
	s->str = malloc(s->size);
	memcpy(s->str, string, s->size);
	return s;
}

Str* str_from_char(char ch)
{
	return NULL;
}
