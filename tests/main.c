#include "debug.h"
#include "token.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

int test_let_statements(void)
{
	// I will write the test later
	const char *input = "let x = 5;\n"
	"let y = 10;\n"
	"let foobar = 838383;";
	return 0;
}

int test_lexer_simple(void)
{
	const char* input = "=+(){},;";
	struct expected {
		token_type expected_type;
		const char* expected_literal;
	};

	struct expected tests[] = {
		{ASSIGN, "="},
		{PLUS, "+"},
		{LPAREN, "("},
		{RPAREN, ")"},
		{LBRACE, "{"},
		{RBRACE, "}"},
		{COMMA, ","},
		{SEMICOLON, ";"},
		{MEOF, "\0"},
	};

	size_t length = sizeof(tests) / sizeof(tests[0]);

	if (lexer_init(input))
		return -1;

	for (size_t i = 0; i < length; i++) {
		if (lexer_next_token())
			return -1;
		assert(tok->type == tests[i].expected_type);
		assert(strncmp(tok->literal, tests[i].expected_literal, strlen(tok->literal)) == 0);
		token_destroy(tok);
	}
	lexer_destroy();
	return 0;
}

int test_lexer_complex(void)
{
	const char* input = "let five = 5;\n"
	"let ten = 10;\n"

	"let add = fn(x, y) {\n"
		"\tx + y;\n"
	"};\n"

	"let result = add(five, ten);"
	"!-/*5;"
	"5 < 10 > 5;"

	"if (5 < 10) {"
		"\treturn true;"
	"} else {"
		"\treturn false;"
	"}"

	"10 == 10;"
	"10 != 9;";

	struct expected {
		token_type expected_type;
		const char* expected_literal;
	};

	struct expected tests[] = {
		{LET, "let"},
		{IDENT, "five"},
		{ASSIGN, "="},
		{INT, "5"},
		{SEMICOLON, ";"},
		{LET, "let"},
		{IDENT, "ten"},
		{ASSIGN, "="},
		{INT, "10"},
		{SEMICOLON, ";"},
		{LET, "let"},
		{IDENT, "add"},
		{ASSIGN, "="},
		{FUNCTION, "fn"},
		{LPAREN, "("},
		{IDENT, "x"},
		{COMMA, ","},
		{IDENT, "y"},
		{RPAREN, ")"},
		{LBRACE, "{"},
		{IDENT, "x"},
		{PLUS, "+"},
		{IDENT, "y"},
		{SEMICOLON, ";"},
		{RBRACE, "}"},
		{SEMICOLON, ";"},
		{LET, "let"},
		{IDENT, "result"},
		{ASSIGN, "="},
		{IDENT, "add"},
		{LPAREN, "("},
		{IDENT, "five"},
		{COMMA, ","},
		{IDENT, "ten"},
		{RPAREN, ")"},
		{SEMICOLON, ";"},
		{BANG, "!"},
		{MINUS, "-"},
		{SLASH, "/"},
		{ASTERISK, "*"},
		{INT, "5"},
		{SEMICOLON, ";"},
		{INT, "5"},
		{LT, "<"},
		{INT, "10"},
		{GT, ">"},
		{INT, "5"},
		{SEMICOLON, ";"},
		{IF, "if"},
		{LPAREN, "("},
		{INT, "5"},
		{LT, "<"},
		{INT, "10"},
		{RPAREN, ")"},
		{LBRACE, "{"},
		{RETURN, "return"},
		{TRUE, "true"},
		{SEMICOLON, ";"},
		{RBRACE, "}"},
		{ELSE, "else"},
		{LBRACE, "{"},
		{RETURN, "return"},
		{FALSE, "false"},
		{SEMICOLON, ";"},
		{RBRACE, "}"},
		{INT, "10"},
		{EQ, "=="},
		{INT, "10"},
		{SEMICOLON, ";"},
		{INT, "10"},
		{NOT_EQ, "!="},
		{INT, "9"},
		{SEMICOLON, ";"},
		{MEOF, "\0"}
	};

	size_t length = sizeof(tests) / sizeof(tests[0]);

	if (lexer_init(input))
		return -1;

	for (size_t i = 0; i < length; i++) {
		if (lexer_next_token())
			return -1;
		print_token();
		assert(tok->type == tests[i].expected_type);
		assert(strncmp(tok->literal, tests[i].expected_literal, strlen(tok->literal)) == 0);
		token_destroy(tok);
	}
	lexer_destroy();
	return 0;
}

int main(void)
{
	if (init_keywords())
		return -1;
	if (test_lexer_complex())
		return -1;
	if (test_lexer_simple())
		return -1;

	free_keywords();
	return 0;
}
