#include "debug.h"
#include "token.h"
#include "lexer.h"
#include <stdio.h>
#include <stdbool.h>

#define TOKEN_TYPE(type, name) \
	case (type):\
		printf(" Literal:%s\n", (name));\
		break\

void print_token(void)
{
	printf("Type: %s", tok->literal);
	switch(tok->type)
	{
		TOKEN_TYPE(MILLEGAL, "MILLEGAL");
		TOKEN_TYPE(MEOF, "MEOF");
		TOKEN_TYPE(IDENT, "INDENT");
		TOKEN_TYPE(INT, "INT");
		TOKEN_TYPE(ASSIGN, "ASSIGN");
		TOKEN_TYPE(PLUS, "PLUS");
		TOKEN_TYPE(MINUS, "MINUS");
		TOKEN_TYPE(BANG, "BANG");
		TOKEN_TYPE(ASTERISK, "ASTERISK");
		TOKEN_TYPE(SLASH, "SLASH");
		TOKEN_TYPE(LT, "LT");
		TOKEN_TYPE(GT, "GT");
		TOKEN_TYPE(COMMA, "COMMA");
		TOKEN_TYPE(SEMICOLON, "SEMICOLON");
		TOKEN_TYPE(LPAREN, "LPAREN");
		TOKEN_TYPE(RPAREN, "RPAREN");
		TOKEN_TYPE(LBRACE, "LBRACE");
		TOKEN_TYPE(RBRACE, "RBRACE");
		TOKEN_TYPE(FUNCTION, "FUNCTION");
		TOKEN_TYPE(LET, "LET");
		TOKEN_TYPE(TRUE, "TRUE");
		TOKEN_TYPE(FALSE, "FALSE");
		TOKEN_TYPE(IF, "IF");
		TOKEN_TYPE(ELSE, "ELSE");
		TOKEN_TYPE(RETURN, "RETURN");
		TOKEN_TYPE(EQ, "EQ");
		TOKEN_TYPE(NOT_EQ, "NOT_EQ");
	}
}

void print_lexer_state(void)
{
	printf("input: %s\ninput size: %lu\n", l->input, l->input_len);
	printf("position: %zu, read_position: %zu\n", l->position, l->read_position);
	printf("current ch: %c\n", l->ch);
}

void print_bool(bool x) {
	if (x) {
		printf("true");
	} else {
		printf("false");
	}
}
