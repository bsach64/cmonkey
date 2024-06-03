#include <stdlib.h>

#include "token.h"

struct token* token_init(Str* s, Token_Type tt)
{
	struct token* tok = malloc(sizeof(*tok));
	tok->literal = s;
	tok->type = tt;
	return tok;
}

void token_destroy(struct token* t)
{
	free(t->literal->str);
	free(t->literal);
	free(t);
}
