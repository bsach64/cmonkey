#ifndef DEBUG_H
#define DEBUG_H

#include "token.h"
#include "lexer.h"
#include "hashtable.h"

void print_token(struct token* tok);
void print_lexer_state(struct lexer *l);
void print_hash_table(hash_table* h);
void print_hash_table_debug(hash_table* h);

#endif // !DEBUG_H
