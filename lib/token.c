#include <stdlib.h>

#include "token.h"
#include "hashtable.h"

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

Token_Type lookup_indent(Str* indentifier)
{
	Token_Type t = IDENT;
	Hash_Table* keywords = hash_table_init(4);
	keywords = hash_table_insert(keywords, "fn", FUNCTION);
	keywords = hash_table_insert(keywords, "let", LET);

	if (hash_table_search(keywords, indentifier->str)) {
		t = hash_table_get(keywords, indentifier->str);
	}
	hash_table_destroy(keywords);
	return t;
}
