#include <unistd.h>
#include <stdlib.h>

#define STR_BUFFER_SIZE 8

struct str {
	char* string;
	size_t position;
	size_t length;
	size_t bufsize;
};

#define str_append(l, x) \
	do {\
		if ((l)->position >= (l)->bufsize) {\
			if ((l)->bufsize == 0) (l)->bufsize = STR_BUFFER_SIZE;\
			else (l)->bufsize *= 2;\
			(l)->string = realloc((l)->string, ((l)->bufsize)*sizeof(*(l)->string));\
		}\
		(l)->string[(l)->position++] = x;\
		(l)->length++;\
	} while(0)

char* get_string(struct str* s);
struct str* new_str(void);
void free_str(struct str* s);
