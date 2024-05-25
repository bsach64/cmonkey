#include "arena.h"
#include "str.h"

#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
	MILLEGAL,
	MEOF,
	IDENT,
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
} Token_Type; 

struct token {
	Token_Type type;
	Str* literal;
};

struct token* token_init(Arena* arena, Str* s, Token_Type tt);

#endif // !TOKEN_H
