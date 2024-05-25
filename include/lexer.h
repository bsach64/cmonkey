#ifndef LEXER_H
#define LEXER_H

#include "arena.h"
#include "token.h"
#include "str.h"

struct lexer {
	Str* input;
	u64 position;
	u64 read_position;
	char ch;
};

struct lexer* lexer_init(Arena* lexer_arena, const char* input);
void lexer_read_char(struct lexer* l);
struct token* lexer_next_token(Arena* tok_arena, struct lexer* l);
Str* lexer_read_indentifier(Arena* tok_arena, struct lexer* l);

#endif // !LEXER_H
