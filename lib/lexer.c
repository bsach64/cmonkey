#include <string.h>
#include "arena.h"
#include "lexer.h"

struct lexer* lexer_init(Arena* lexer_arena, const char* input)
{
	struct lexer* l = arena_alloc(lexer_arena, sizeof(struct lexer));
	l->input = arena_alloc(lexer_arena, sizeof(str));
	l->input->size = strlen(input);
	l->input->str = arena_alloc(lexer_arena, l->input->size);
	memcpy(l->input->str, input, l->input->size);
	l->read_position = 0;
	l->ch = '\0';
	l->position = 0;

	lexer_read_char(l);
	return l;
}

void lexer_read_char(struct lexer* l) 
{
	if (l->read_position >= l->input->size) {
		l->ch = 0;
	} else {
		l->ch = l->input->str[l->read_position];
	}
	l->position = l->read_position;
	l->read_position += 1;
}

struct token* lexer_next_token(Arena* tok_arena, struct lexer* l)
{
	struct token* tok;

	switch(l->ch)
	{
		case '=':
			tok = token_init(tok_arena, &(l->ch), ASSIGN);
			break;
		case ';':
			tok = token_init(tok_arena, &(l->ch), SEMICOLON);
			break;
		case '(':
			tok = token_init(tok_arena, &(l->ch), LPAREN);
			break;
		case ')':
			tok = token_init(tok_arena, &(l->ch), RPAREN);
			break;
		case ',':
			tok = token_init(tok_arena, &(l->ch), COMMA);
			break;
		case '+':
			tok = token_init(tok_arena, &(l->ch), PLUS);
			break;
		case '{':
			tok = token_init(tok_arena, &(l->ch), LBRACE);
			break;
		case '}':
			tok = token_init(tok_arena, &(l->ch), RBRACE);
			break;
		case 0:
			tok = token_init(tok_arena, "\0", MEOF);
			break;
	}

	lexer_read_char(l);
	return tok;
}
