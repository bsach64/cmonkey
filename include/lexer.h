#ifndef LEXER_H
#define LEXER_H

#include "arena.h"
#include "token.h"

struct lexer {
	Str* input;
	size_t position;
	size_t read_position;
	char ch;
};

struct lexer* lexer_init(Arena* lexer_arena, const char* input);
void lexer_read_char(struct lexer* l);
struct token* lexer_next_token(Arena* tok_arena, struct lexer* l);

#endif // !LEXER_H
