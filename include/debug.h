#ifndef DEBUG_H
#define DEBUG_H

#include "token.h"
#include "lexer.h"
#include "hashtable.h"

void print_token_type(struct token* tok);
void print_lexer_state(struct lexer *l);
void print_hash_table(Hash_Table* h);
void print_hash_table_debug(Hash_Table* h);

#endif // !DEBUG_H
