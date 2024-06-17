#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include "str.h"

struct lexer {
	Str* input;
	u64 position;
	u64 read_position;
	char ch;
};

struct lexer* lexer_init(const char* input);
void lexer_read_char(struct lexer* l);
char lexer_peek_char(struct lexer* l);
struct token* lexer_next_token(struct lexer* l);
Str* lexer_read_indentifier(struct lexer* l);
Str* lexer_read_number(struct lexer* l);
void lexer_destroy(struct lexer* l);

#endif // !LEXER_H
