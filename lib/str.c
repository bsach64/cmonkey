#include "str.h"
#include "arena.h"
#include <string.h>

Str* str_from_cstr(Arena* arena, const char* string)
{
	Str* s = arena_alloc(arena, sizeof(*s));
	s->size = strlen(string);
	s->str = arena_alloc(arena, s->size);
	memcpy(s->str, string, s->size);
	return s;
}

Str* str_from_char(Arena* arena, char ch)
{
	Str* s = arena_alloc(arena, sizeof(*s));
	s->size = 1;
	s->str = arena_alloc(arena, s->size);
	s->str[0] = ch;
	return s;
}
