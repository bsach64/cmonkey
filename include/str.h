#ifndef STR_H
#define STR_H

#include "arena.h"

typedef struct {
	char* str;
	u64 size;
} Str;

Str* str_from_cstr(Arena* arena, const char* string);
Str* str_from_char(Arena* arena, char ch);
Str* str_from_cstr_malloc(const char* string);

#endif // !STR_H
