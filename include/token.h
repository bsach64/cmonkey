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

struct token* token_init(Str* s, Token_Type tt);
void token_destroy(struct token* t);
Token_Type lookup_indent(Str* indentifier);

#endif // !TOKEN_H
