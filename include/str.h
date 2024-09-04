#ifndef STR_H
#define STR_H

#include "types.h"

typedef struct {
	char* str;
	u64 size;
} string;

string* str_from_cstr(const char* string);
string* str_from_char(char ch);

#endif // !STR_H
