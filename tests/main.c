#include "arena.h"
#include "hashtable.h"
#include "str.h"
#include "token.h"
#include "lexer.h"
#include "debug.h"
#include <string.h>
#include <assert.h>

void test_hash_table(void)
{
	Arena* arena = arena_init();
	Hash_Table* h = hash_table_init(1);
	Str* s = str_from_cstr(arena, "hey");
	h = insert(h, s, 2);
	Str* x = str_from_cstr(arena, "bhee");
	h = insert(h, x, 4);
	print_hash_table(h);
	arena_destroy(arena);
	hash_table_destroy(h);
}

void test_arena(void)
{
	Arena* arena = arena_init();
	assert(arena->buf_len == 0);
	arena_alloc(arena, 1);
	assert(arena->buf_len == 1);
	arena_alloc(arena, 1);
	assert(arena->buf_len == 2);
	arena_destroy(arena);
}

void test_lexer_simple(void)
{
	const char* input = "=+(){},;";
	struct expected {
		Token_Type expected_type;
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

	Arena* arena = arena_init();
	print_arena_state(arena);
	struct lexer* l = lexer_init(arena, input);
	print_lexer_state(l);
	print_arena_state(arena);

	for (u64 i = 0; i < length; i++) {
		Temp_Arena_Memory temp = temp_area_memory_begin(arena);
		struct token* tok = lexer_next_token(arena, l);
		print_arena_state(arena);
		print_token_type(tok);
		assert(tok->type == tests[i].expected_type);
		assert(strncmp(tok->literal->str, tests[i].expected_literal, tok->literal->size) == 0);
		temp_area_memory_end(temp);
	}
	arena_destroy(arena);
}

void test_lexer_complex(void)
{
	const char* input = "let five = 5;\n"
	"let ten = 10;\n"

	"let add = fn(x, y) {\n"
		"\tx + y;\n"
	"};\n"

	"let result = add(five, ten);";

	struct expected {
		Token_Type expected_type;
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
		{MEOF, "\0"}
	};

	u64 length = sizeof(tests) / sizeof(tests[0]);

	Arena* arena = arena_init();
	print_arena_state(arena);
	struct lexer* l = lexer_init(arena, input);
	print_lexer_state(l);
	print_arena_state(arena);

	for (u64 i = 0; i < length; i++) {
		Temp_Arena_Memory temp = temp_area_memory_begin(arena);
		struct token* tok = lexer_next_token(arena, l);
		print_arena_state(arena);
		print_token_type(tok);
		assert(tok->type == tests[i].expected_type);
		assert(strncmp(tok->literal->str, tests[i].expected_literal, tok->literal->size) == 0);
		temp_area_memory_end(temp);
	}
	arena_destroy(arena);
}

int main(void)
{
	test_arena();
	test_lexer_simple();
	test_hash_table();
}
