#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"
#include "str.h"
#include <stdio.h>

static bool is_letter(char ch)
{
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

static void skip_whitespace(struct lexer* l)
{
	while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
		lexer_read_char(l);
	}
}

static bool is_digit(char ch)
{
	return '0' <= ch && ch <= '9';
}

struct lexer* lexer_init(const char* input)
{
	struct lexer* l = malloc(sizeof(*l));
	l->input = str_from_cstr(input);
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

struct token* lexer_next_token(struct lexer* l)
{
	struct token* tok;
	
	skip_whitespace(l);
	switch(l->ch)
	{
		case '=':
			if (lexer_peek_char(l) == '=') {
				lexer_read_char(l);
				tok = token_init(str_from_cstr("=="), EQ);
			} else {
				tok = token_init(str_from_char(l->ch), ASSIGN);
			}
			break;
		case '+':
			tok = token_init(str_from_char(l->ch), PLUS);
			break;
		case '-':
			tok = token_init(str_from_char(l->ch), MINUS);
			break;
		case '!':
			if (lexer_peek_char(l) == '=') {
				lexer_read_char(l);
				tok = token_init(str_from_cstr("!="), NOT_EQ);
			} else {
				tok = token_init(str_from_char(l->ch), BANG);
			}
			break;
		case '/':
			tok = token_init(str_from_char(l->ch), SLASH);
			break;
		case '*':
			tok = token_init(str_from_char(l->ch), ASTERISK);
			break;
		case '<':
			tok = token_init(str_from_char(l->ch), LT);
			break;
		case '>':
			tok = token_init(str_from_char(l->ch), GT);
			break;
		case ';':
			tok = token_init(str_from_char(l->ch), SEMICOLON);
			break;
		case '(':
			tok = token_init(str_from_char(l->ch), LPAREN);
			break;
		case ')':
			tok = token_init(str_from_char(l->ch), RPAREN);
			break;
		case ',':
			tok = token_init(str_from_char(l->ch), COMMA);
			break;
		case '{':
			tok = token_init(str_from_char(l->ch), LBRACE);
			break;
		case '}':
			tok = token_init(str_from_char(l->ch), RBRACE);
			break;
		case 0:
			tok = token_init(str_from_char('\0'), MEOF);
			break;
		default:
			if (is_letter(l->ch)) {
				string* indentifier = lexer_read_indentifier(l);
				token_type tt = lookup_indent(indentifier);
				tok = token_init(indentifier, tt);
				return tok;
			} else if (is_digit(l->ch)) {
				tok = token_init(lexer_read_number(l), INT);
				return tok;
			} else {
				tok = token_init(str_from_char(l->ch), MILLEGAL);
				return tok;
			}
			break;
	}

	lexer_read_char(l);
	return tok;
}

string* lexer_read_indentifier(struct lexer* l)
{
	u64 start = l->position;
	while (is_letter(l->ch))
		lexer_read_char(l);

	u64 end = l->position;
	string* s = malloc(sizeof(*s));
	s->size = end - start;
	s->str = malloc(s->size + 1);
	for (u64 i = 0; i < s->size; i++)
		s->str[i] = l->input->str[start + i];
	s->str[s->size] = '\0';
	return s;
}

string* lexer_read_number(struct lexer* l)
{
	u64 start = l->position;
	while (is_digit(l->ch))
		lexer_read_char(l);

	u64 end = l->position;
	string* s = malloc(sizeof(*s));
	s->size = end - start;
	s->str = malloc(s->size + 1);
	for (u64 i = 0; i < s->size; i++)
		s->str[i] = l->input->str[start + i];
	s->str[s->size] = '\0';
	return s;
}

char lexer_peek_char(struct lexer* l)
{
	if (l->read_position >= l->input->size) {
		return 0;
	}
	return l->input->str[l->read_position];
}

void lexer_destroy(struct lexer* l)
{
	free(l->input->str);
	free(l->input);
	free(l);
}
