#include "hashtable.h"
#include "str.h"
#include "token.h"
#include "lexer.h"
#include <string.h>
#include <assert.h>

void test_hash_table(void)
{
	Hash_Table* h = hash_table_init(3);
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
	// const char* input = "let five = 5;\n"
	// "let ten = 10;\n"
	//
	// "let add = fn(x, y) {\n"
	// 	"\tx + y;\n"
	// "};\n"
	//
	// "let result = add(five, ten);";
	//
	// struct expected {
	// 	Token_Type expected_type;
	// 	const char* expected_literal;
	// };
	//
	// struct expected tests[] = {
	// 	{LET, "let"},
	// 	{IDENT, "five"},
	// 	{ASSIGN, "="},
	// 	{INT, "5"},
	// 	{SEMICOLON, ";"},
	// 	{LET, "let"},
	// 	{IDENT, "ten"},
	// 	{ASSIGN, "="},
	// 	{INT, "10"},
	// 	{SEMICOLON, ";"},
	// 	{LET, "let"},
	// 	{IDENT, "add"},
	// 	{ASSIGN, "="},
	// 	{FUNCTION, "fn"},
	// 	{LPAREN, "("},
	// 	{IDENT, "x"},
	// 	{COMMA, ","},
	// 	{IDENT, "y"},
	// 	{RPAREN, ")"},
	// 	{LBRACE, "{"},
	// 	{IDENT, "x"},
	// 	{PLUS, "+"},
	// 	{IDENT, "y"},
	// 	{SEMICOLON, ";"},
	// 	{LET, "let"},
	// 	{IDENT, "result"},
	// 	{ASSIGN, "="},
	// 	{IDENT, "add"},
	// 	{LPAREN, "("},
	// 	{IDENT, "five"},
	// 	{COMMA, ","},
	// 	{IDENT, "ten"},
	// 	{RPAREN, ")"},
	// 	{SEMICOLON, ";"},
	// 	{MEOF, "\0"}
	// };
	//
	// u64 length = sizeof(tests) / sizeof(tests[0]);
	//
	// Arena* arena = arena_init();
	// print_arena_state(arena);
	// struct lexer* l = lexer_init(arena, input);
	// print_lexer_state(l);
	// print_arena_state(arena);
	//
	// for (u64 i = 0; i < length; i++) {
	// 	Temp_Arena_Memory temp = temp_area_memory_begin(arena);
	// 	struct token* tok = lexer_next_token(arena, l);
	// 	print_arena_state(arena);
	// 	print_token_type(tok);
	// 	assert(tok->type == tests[i].expected_type);
	// 	assert(strncmp(tok->literal->str, tests[i].expected_literal, tok->literal->size) == 0);
	// 	temp_area_memory_end(temp);
	// }
	// arena_destroy(arena);
}

int main(void)
{
	test_lexer_simple();
	test_hash_table();
}
