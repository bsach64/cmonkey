#include "arena.h"
#include "token.h"
#include "lexer.h"
#include "debug.h"
#include <string.h>
#include <assert.h>

void test_arena()
{
	Arena* arena = arena_init();
	assert(arena->buf_len == 0);
	arena_alloc(arena, 1);
	assert(arena->buf_len == 1);
	arena_alloc(arena, 1);
	assert(arena->buf_len == 2);
	arena_destroy(arena);
}

void test_lexer()
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

	Arena* arena = arena_init();
	print_arena_state(arena);
	struct lexer* l = lexer_init(arena, input);
	print_lexer_state(l);
	print_arena_state(arena);
	
	for (size_t i = 0; i < length; i++) {
		struct token* tok = lexer_next_token(arena, l);
		print_arena_state(arena);
		print_token_type(tok);
		assert(tok->type == tests[i].expected_type);
		assert(strncmp(tok->literal->str, tests[i].expected_literal, tok->literal->size) == 0);
	}
	arena_destroy(arena);
}

int main(void)
{
	test_arena();
	test_lexer();
}
