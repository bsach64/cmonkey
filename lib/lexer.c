#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"
#include "token.h"

struct lexer *l;

static bool is_letter(char ch)
{
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

static void skip_whitespace(void)
{
	while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
		lexer_read_char();
	}
}

static bool is_digit(char ch)
{
	return '0' <= ch && ch <= '9';
}

int lexer_init(const char* input)
{
	l = malloc(sizeof(*l));
	if (!l)
		return -1;

	l->input_len = strlen(input);
	l->input = malloc(l->input_len + 1);
	if (!l->input)
		return -1;
	strcpy(l->input, input);
	l->read_position = 0;
	l->ch = '\0';
	l->position = 0;

	lexer_read_char();
	return 0;
}

void lexer_read_char(void)
{
	if (l->read_position >= l->input_len) {
		l->ch = 0;
	} else {
		l->ch = l->input[l->read_position];
	}
	l->position = l->read_position;
	l->read_position += 1;
}

int lexer_next_token(void)
{
	skip_whitespace();
	switch(l->ch)
	{
		case '=':
			if (lexer_peek_char() == '=') {
				lexer_read_char();
				if (token_str_init("==", EQ))
					return -1;
			} else {
				if (token_char_init(l->ch, ASSIGN))
					return -1;
			}
			break;
		case '+':
			if (token_char_init(l->ch, PLUS))
				return -1;
			break;
		case '-':
			if (token_char_init(l->ch, MINUS))
				return -1;
			break;
		case '!':
			if (lexer_peek_char() == '=') {
				lexer_read_char();
				if (token_str_init("!=", NOT_EQ))
					return -1;
			} else {
				if (token_char_init(l->ch, BANG))
					return -1;
			}
			break;
		case '/':
			if (token_char_init(l->ch, SLASH))
				return -1;
			break;
		case '*':
			if (token_char_init(l->ch, ASTERISK))
				return -1;
			break;
		case '<':
			if (token_char_init(l->ch, LT))
				return -1;
			break;
		case '>':
			if (token_char_init(l->ch, GT))
				return -1;
			break;
		case ';':
			if (token_char_init(l->ch, SEMICOLON))
				return -1;
			break;
		case '(':
			if (token_char_init(l->ch, LPAREN))
				return -1;
			break;
		case ')':
			if (token_char_init(l->ch, RPAREN))
				return -1;
			break;
		case ',':
			if (token_char_init(l->ch, COMMA))
				return -1;
			break;
		case '{':
			if (token_char_init(l->ch, LBRACE))
				return -1;
			break;
		case '}':
			if (token_char_init(l->ch, RBRACE))
				return -1;
			break;
		case 0:
			if (token_char_init(l->ch, MEOF))
				return -1;
			break;
		default:
			if (is_letter(l->ch)) {
				char* indentifier = lexer_read_indentifier();
				if (!indentifier)
					return -1;
				token_type tt = lookup_indent(indentifier);
				if (token_str_init(indentifier, tt))
					return -1;
				free(indentifier);
				return 0;
			} else if (is_digit(l->ch)) {
				char* number = lexer_read_number();
				if (!number)
					return -1;
				if (token_str_init(number, INT))
					return -1;
				free(number);
				return 0;
			} else {
				if (token_char_init(l->ch, MILLEGAL))
					return -1;
			}
			break;
	}

	lexer_read_char();
	return 0;
}

char* lexer_read_indentifier(void)
{
	size_t start = l->position;
	while (is_letter(l->ch))
		lexer_read_char();

	size_t end = l->position;
	size_t size = end - start;
	char *indentifier = malloc(size + 1);
	if (!indentifier)
		return NULL;
	for (size_t i = 0; i < size; i++)
		indentifier[i] = l->input[start + i];
	indentifier[size] = '\0';
	return indentifier;
}

char* lexer_read_number(void)
{
	size_t start = l->position;
	while (is_digit(l->ch))
		lexer_read_char();

	size_t end = l->position;
	size_t size = end - start;
	char *number = malloc(size + 1);
	if (!number)
		return NULL;
	for (size_t i = 0; i < size; i++)
		number[i] = l->input[start + i];
	number[size] = '\0';
	return number;
}

char lexer_peek_char(void)
{
	if (l->read_position >= l->input_len) {
		return 0;
	}
	return l->input[l->read_position];
}

void lexer_destroy(void)
{
	free(l->input);
	free(l);
}
