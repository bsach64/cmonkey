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
	MINUS,
	BANG,
	ASTERISK,
	SLASH,
	LT,
	GT,
	COMMA,
	SEMICOLON,
	LPAREN,
	RPAREN,
	LBRACE,
	RBRACE,
	FUNCTION,
	LET,
	TRUE,
	FALSE,
	IF,
	ELSE,
	RETURN,
	EQ,
	NOT_EQ
} token_type; 

struct token {
	token_type type;
	string* literal;
};

struct token* token_init(string* s, token_type tt);
void token_destroy(struct token* t);
token_type lookup_indent(string* indentifier);

#endif // !TOKEN_H
