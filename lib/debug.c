#include "debug.h"
#include "token.h"
#include "arena.h"
#include <stdio.h>


#define TOKEN_TYPE(type, name) \
	case (type):\
		printf("%s\n", (name));\
		break\

void print_token_type(struct token* tok)
{
	switch(tok->type)
	{
		TOKEN_TYPE(MILLEGAL, "MILLEGAL");
		TOKEN_TYPE(MEOF, "MEOF");
		TOKEN_TYPE(IDENT, "INDENT");
		TOKEN_TYPE(INT, "INT");
		TOKEN_TYPE(ASSIGN, "ASSIGN");
		TOKEN_TYPE(PLUS, "PLUS");
		TOKEN_TYPE(COMMA, "COMMA");
		TOKEN_TYPE(SEMICOLON, "SEMICOLON");
		TOKEN_TYPE(LPAREN, "LPAREN");
		TOKEN_TYPE(RPAREN, "RPAREN");
		TOKEN_TYPE(LBRACE, "LBRACE");
		TOKEN_TYPE(RBRACE, "RBRACE");
		TOKEN_TYPE(FUNCTION, "FUNCTION");
		TOKEN_TYPE(LET, "LET");
	}
}

void print_lexer_state(struct lexer *l)
{
	printf("input: %.*s\ninput size: %zu\n", (int)l->input->size, l->input->str, l->input->size);
	printf("position: %zu, read_position: %zu\n", l->position, l->read_position);
	printf("current ch: %c\n", l->ch);
}

void print_arena_state(Arena* arena)
{
	printf("buf_len: %zu, cur_offset: %zu\n", arena->buf_len, arena->cur_offset);
}
