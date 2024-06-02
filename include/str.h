#ifndef STR_H
#define STR_H

#include "types.h"

typedef struct {
	char* str;
	u64 size;
} Str;

Str* str_from_cstr(const char* string);

#endif // !STR_H
