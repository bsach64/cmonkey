#include <string.h>
#include <stdbool.h>
#include "arena.h"
#include "lexer.h"
#include "str.h"

static bool is_letter(char ch)
{
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

struct lexer* lexer_init(Arena* lexer_arena, const char* input)
{
	struct lexer* l = arena_alloc(lexer_arena, sizeof(*l));
	l->input = str_from_cstr(lexer_arena, input);
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
			tok = token_init(tok_arena, str_from_char(tok_arena, l->ch), ASSIGN);
			break;
		case ';':
			tok = token_init(tok_arena, str_from_char(tok_arena, l->ch), SEMICOLON);
			break;
		case '(':
			tok = token_init(tok_arena, str_from_char(tok_arena, l->ch), LPAREN);
			break;
		case ')':
			tok = token_init(tok_arena, str_from_char(tok_arena, l->ch), RPAREN);
			break;
		case ',':
			tok = token_init(tok_arena, str_from_char(tok_arena, l->ch), COMMA);
			break;
		case '+':
			tok = token_init(tok_arena, str_from_char(tok_arena, l->ch), PLUS);
			break;
		case '{':
			tok = token_init(tok_arena, str_from_char(tok_arena, l->ch), LBRACE);
			break;
		case '}':
			tok = token_init(tok_arena, str_from_char(tok_arena, l->ch), RBRACE);
			break;
		case 0:
			tok = token_init(tok_arena, str_from_char(tok_arena, '\0'), MEOF);
			break;
		default:
			if (is_letter(l->ch)) {
				tok = token_init(
					tok_arena,
					lexer_read_indentifier(tok_arena, l),
					IDENT
				);
				return tok;
			} else {
				tok = token_init(tok_arena, str_from_char(tok_arena, l->ch), MILLEGAL);
				
			}
			break;
	}

	lexer_read_char(l);
	return tok;
}

Str* lexer_read_indentifier(Arena* tok_arena, struct lexer* l)
{
	u64 start = l->position;
	while (is_letter(l->ch))
		lexer_read_char(l);

	u64 end = l->position;
	Str* s = arena_alloc(tok_arena, sizeof(*s));
	s->size = end - start;
	s->str = arena_alloc(tok_arena, s->size);
	for (u64 i = start; i < end; i++)
		s->str[i] = l->input->str[i];
	return s;
}
