#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "list.h"
#include "gc.h"

#define KEYWORD_TABLE_SIZE 32
#define INSERT_KEYWORD(ptr, str, tok)			\
do {							\
	struct keyword_entry *(ptr) = NULL;		\
	if (init_keyword_entry((str), (tok), (ptr)))   \
		goto err;				\
							\
} while(0)

#define RETURN_STR(t, s)	\
	case (t):		\
		return (s);	\

static struct hlist_head keywords[32];
struct token *tok;

struct keyword_entry {
	char* keyword;
	token_type t;
	struct hlist_node hash;
};

char* token_type_to_str(token_type tt) {
	switch(tt)
	{
		RETURN_STR(MILLEGAL, "MILLEGAL");
		RETURN_STR(MEOF, "MEOF");
		RETURN_STR(IDENT, "INDENT");
		RETURN_STR(INT, "INT");
		RETURN_STR(ASSIGN, "ASSIGN");
		RETURN_STR(PLUS, "PLUS");
		RETURN_STR(MINUS, "MINUS");
		RETURN_STR(BANG, "BANG");
		RETURN_STR(ASTERISK, "ASTERISK");
		RETURN_STR(SLASH, "SLASH");
		RETURN_STR(LT, "LT");
		RETURN_STR(GT, "GT");
		RETURN_STR(COMMA, "COMMA");
		RETURN_STR(SEMICOLON, "SEMICOLON");
		RETURN_STR(LPAREN, "LPAREN");
		RETURN_STR(RPAREN, "RPAREN");
		RETURN_STR(LBRACE, "LBRACE");
		RETURN_STR(RBRACE, "RBRACE");
		RETURN_STR(FUNCTION, "FUNCTION");
		RETURN_STR(LET, "LET");
		RETURN_STR(TRUE, "TRUE");
		RETURN_STR(FALSE, "FALSE");
		RETURN_STR(IF, "IF");
		RETURN_STR(ELSE, "ELSE");
		RETURN_STR(RETURN, "RETURN");
		RETURN_STR(EQ, "EQ");
		RETURN_STR(NOT_EQ, "NOT_EQ");
	}
}

int init_keyword_entry(const char* word, token_type t, struct keyword_entry* entry)
{
	entry = gc_malloc(sizeof(*entry));
	if (!entry)
		return -1;

	entry->keyword = gc_malloc(strlen(word) + 1);
	if (!entry->keyword)
		return -1;

	strcpy(entry->keyword, word);
	entry->t = t;
	INIT_HLIST_NODE(&entry->hash);
	hlist_add_head(&entry->hash, &keywords[strlen(word) % KEYWORD_TABLE_SIZE]);

	return 0;
}

void free_keywords(void)
{
	struct keyword_entry *word;
	struct hlist_node *tmp;

	for (int i = 0; i < KEYWORD_TABLE_SIZE; i++) {
		hlist_for_each_entry_safe(word, tmp, &keywords[i], hash) {
			gc_free(word->keyword);
			gc_free(word);
		}
		INIT_HLIST_HEAD(&keywords[i]);
	}
}

int init_keywords(void)
{
	for (int i = 0; i < KEYWORD_TABLE_SIZE; i++)
		INIT_HLIST_HEAD(&keywords[i]);

	INSERT_KEYWORD(fn, "fn", FUNCTION);
	INSERT_KEYWORD(let, "let", LET);
	INSERT_KEYWORD(mtrue, "true", TRUE);
	INSERT_KEYWORD(mfalse, "false", FALSE);
	INSERT_KEYWORD(mif, "if", IF);
	INSERT_KEYWORD(melse, "else", ELSE);
	INSERT_KEYWORD(mreturn, "return", RETURN);
	return 0;
err:
	return -1;
}

int token_char_init(char s, token_type tt)
{
	tok = gc_malloc(sizeof(*tok));
	if (!tok)
		return -1;

	tok->literal = gc_malloc(2);
	if (!tok->literal) {
		gc_free(tok);
		return -1;
	}

	tok->literal[0] = s;
	tok->literal[1] = '\0';
	tok->type = tt;
	return 0;
}

int token_str_init(const char* s, token_type tt)
{
	tok = gc_malloc(sizeof(*tok));
	if (!tok)
		return -1;

	size_t length = strlen(s);
	tok->literal = gc_malloc(length + 1);
	if (!tok->literal) {
		gc_free(tok);
		return -1;
	}

	strcpy(tok->literal, s);
	tok->type = tt;
	return 0;
}

void token_destroy(struct token *t)
{
	gc_free(t->literal);
	gc_free(t);
}

token_type lookup_indent(char* indentifier)
{
	struct keyword_entry *word;
	struct hlist_head *chain;
	size_t length = strlen(indentifier);

	chain = &keywords[length % KEYWORD_TABLE_SIZE];
	hlist_for_each_entry(word, chain, hash) {
		if (strncmp(word->keyword, indentifier, strlen(word->keyword)) == 0)
			return word->t;
	}
	return IDENT;
}
