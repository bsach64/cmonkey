#ifndef DEBUG_H
#define DEBUG_H

#include "token.h"
#include "lexer.h"

void print_token_type(struct token* tok);
void print_lexer_state(struct lexer *l);
void print_arena_state(Arena* arena);

#endif // !DEBUG_H
