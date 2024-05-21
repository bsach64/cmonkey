#include "str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct str* new_str(void)
{
	struct str* s = malloc(sizeof(struct str));
	if (s == NULL)
		goto err;

	memset(s, 0, sizeof(struct str));
	s->string = NULL;
	return s;

err:
	printf("ERROR: Could not allocate memory\n");
	exit(1);
}

void free_str(struct str* s)
{
	free(s->string);
	free(s);
}

char* get_string(struct str* s)
{
	str_append(s, '\0');
	char* string = (char*) malloc(sizeof(s->length));
	if (string == NULL)
		goto err;

	memcpy(s->string, string, s->length);
	return string;

err:
	printf("ERROR: Could not allocate memory\n");
	exit(1);
}
