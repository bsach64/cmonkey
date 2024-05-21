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

void print_str(struct str* s)
{
	printf("%.*s\n", s->length, s->string);
}
