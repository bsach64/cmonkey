#include "debug.h"
#include "hashtable.h"
#include "str.h"
#include "token.h"
#include "lexer.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

void test_hash_table(void)
{
	hash_table* h = hash_table_init(3);
	assert(h->size == 3);
	h = hash_table_insert(h, "bhavik", 10);
	h = hash_table_insert(h, "sachdev", 20);
	assert(hash_table_search(h, "bhavik") == true);
	assert(hash_table_get(h, "bhavik") == 10);
	h = hash_table_insert(h, "bhavik", 20);
	assert(hash_table_get(h, "bhavik") == 20);
	assert(h->size == 3);
	h = hash_table_insert(h, "noice", 50);
	assert(h->size == 6);
	h = hash_table_insert(h, "please", 60);
	h = hash_table_insert(h, "okay", 100);
	assert(hash_table_search(h, "noice") == true);
	assert(h->size == 12);
	hash_table_destroy(h);
	
	h = hash_table_init(1);
	h = hash_table_delete(h, "bhavik");
	h = hash_table_insert(h, "bhavik", 10);
	assert(h->size == 2);
	h = hash_table_insert(h, "sachdev", 13);
	assert(h->size == 4);
	assert(hash_table_search(h, "bhavik") == true);
	h = hash_table_delete(h, "bhavik");
	assert(hash_table_search(h, "bhavik") == false);
	assert(h->size == 2);
	hash_table_destroy(h);
}

void test_lexer_simple(void)
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

	u64 length = sizeof(tests) / sizeof(tests[0]);

	struct lexer* l = lexer_init(input);

	for (u64 i = 0; i < length; i++) {
		struct token* tok = lexer_next_token(l);
		assert(tok->type == tests[i].expected_type);
		assert(strncmp(tok->literal->str, tests[i].expected_literal, tok->literal->size) == 0);
		token_destroy(tok);
	}
	lexer_destroy(l);
}

void test_lexer_complex(void)
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

	u64 length = sizeof(tests) / sizeof(tests[0]);

	struct lexer* l = lexer_init(input);

	for (u64 i = 0; i < length; i++) {
		struct token* tok = lexer_next_token(l);
		print_token(tok);
		assert(tok->type == tests[i].expected_type);
		assert(strncmp(tok->literal->str, tests[i].expected_literal, tok->literal->size) == 0);
		token_destroy(tok);
	}
	lexer_destroy(l);
}

int main(void)
{
	test_lexer_complex();
	test_lexer_simple();
	test_hash_table();
}
