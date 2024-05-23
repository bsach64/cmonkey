#include "arena.h"
#include "str.h"

#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
	MILLEGAL,
	MEOF,
	INDENT,
	INT,
	ASSIGN,
	PLUS,
	COMMA,
	SEMICOLON,
	LPAREN,
	RPAREN,
	LBRACE,
	RBRACE,
	FUNCTION,
	LET
} token_type; 

struct token {
	token_type type;
	str* literal;
};

struct token* token_init(Arena* arena, const char* string, token_type tt);

#endif // !TOKEN_H
