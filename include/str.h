#ifndef STR_H
#define STR_H

#include "types.h"

typedef struct {
	char* str;
	u64 size;
} Str;

Str* str_from_cstr(const char* string);
Str* str_from_char(char ch);

#endif // !STR_H
