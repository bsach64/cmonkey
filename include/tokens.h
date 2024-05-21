#ifndef TOKENS_H
#define TOKENS_H

#include "str.h"

enum token_type {
	ILLEGAL,
	EOF,
	// identifier
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
};

struct token {
	enum token_type type;
	struct str* literal;
};

#endif // !TOKENS_H
