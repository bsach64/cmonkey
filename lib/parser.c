#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "parser.h"
#include "token.h"
#include "ast.h"
#include "lexer.h"
#include "list.h"
#include "token.h"
#include "gc.h"

struct parser *p;
struct program *prg;

#define PARSE_FN_TABLE_SIZE 16
static struct hlist_head prefix_parse_fn_table[PARSE_FN_TABLE_SIZE];
static struct hlist_head infix_parse_fn_table[PARSE_FN_TABLE_SIZE];

struct prefix_parse_fn {
	struct hlist_node table;
	token_type tt;
	struct expression *(*prefix_parse_fn) (void);
};

struct infix_parse_fn {
	struct hlist_node table;
	token_type tt;
	struct expression *(*infix_parse_fn) (struct expression *);
};

static struct prefix_parse_fn *lookup_prefix_parse_fn(token_type tt)
{
	struct hlist_head *chain;
	struct prefix_parse_fn *prefix;

	chain = &prefix_parse_fn_table[tt % PARSE_FN_TABLE_SIZE];
	hlist_for_each_entry(prefix, chain, table) {
		if (prefix->tt == tt) {
			return prefix;
		}
	}
	return NULL;
}

static struct infix_parse_fn *lookup_infix_parse_fn(token_type tt)
{
	struct hlist_head *chain;
	struct infix_parse_fn *infix;

	chain = &infix_parse_fn_table[tt % PARSE_FN_TABLE_SIZE];
	hlist_for_each_entry(infix, chain, table) {
		if (infix->tt == tt) {
			return infix;
		}
	}
	return NULL;
}

static struct token *copy_tok(void)
{
	size_t len = strlen(p->cur_tok->literal) + 1;
	struct token *dup_tok = gc_malloc(sizeof(*p->cur_tok));
	if (!dup_tok)
		return NULL;

	dup_tok->type = p->cur_tok->type;
	dup_tok->literal = gc_malloc(len);
	if (!dup_tok->literal)
		return NULL;
	memcpy(dup_tok->literal, p->cur_tok->literal, len);
	return dup_tok;
}

int next_token(void)
{
	if (p->cur_tok)
		token_destroy(p->cur_tok);

	p->cur_tok = p->peek_tok;

	if (lexer_next_token())
		return -1;

	p->peek_tok = tok;

	return 0;
}

static struct expression *new_expression(enum expression_type et)
{
	struct expression *exp = gc_malloc(sizeof(*exp));
	if (!exp)
		return NULL;

	exp->token = copy_tok();
	if (!exp->token) {
		gc_free(exp);
		return NULL;
	}

	exp->type = et;
	exp->additional = NULL;
	return exp;
}

static struct expression *parse_identifier(void)
{
	struct expression *eident = new_expression(EINDENTIFIER);
	if (!eident)
		return NULL;

	struct indentifier *ident = gc_malloc(sizeof(*ident));
	if (!ident)
		return NULL;

	size_t ident_len = strlen(eident->token->literal) + 1;
	ident->value = gc_malloc(ident_len);
	if (!ident)
		return NULL;

	memcpy(ident->value, eident->token->literal, ident_len);

	ident->token = copy_tok();
	if (!ident->token)
		return NULL;

	eident->additional = (void *)ident;
	return eident;
}

int new_parser(void)
{
	for (int i = 0; i < PARSE_FN_TABLE_SIZE; i++) {
		INIT_HLIST_HEAD(&prefix_parse_fn_table[i]);
		INIT_HLIST_HEAD(&infix_parse_fn_table[i]);
	}

	p = gc_malloc(sizeof(*p));
	if (!p)
		return -1;

	p->cur_tok = NULL;
	p->peek_tok = NULL;

	if (next_token())
		return -1;

	if (next_token())
		return -1;

	return 0;
}

int cur_token_is(token_type tt)
{
	return tt == p->cur_tok->type;
}

int peek_token_is(token_type tt)
{
	return tt == p->peek_tok->type;
}

int peek_error(token_type t)
{
	char buf[512];
	snprintf(buf, 512, "expected next token to be %s, got %s instead", token_type_to_str(t), token_type_to_str(p->peek_tok->type));
	size_t buf_len = strlen(buf);
	struct error *err = gc_malloc(sizeof(*err));
	if (!err)
		return -1;

	err->error_msg = gc_malloc(buf_len);
	if (!err)
		return -1;

	INIT_LIST_HEAD(&err->next);
	memcpy(err->error_msg, buf, buf_len);
	list_add(&err->next, &prg->error_list);
	return 0;
}

int expect_peek(token_type tt)
{
	if (peek_token_is(tt)) {
		if (next_token())
			return -1;
		return 1;
	}
	if (peek_error(tt))
		return -1;
	return 0;
}

/* Does not allocate memory according to statement_type so void *additional -> NULL */
struct statement *new_statement(enum statement_type st)
{
	struct statement *stmt = gc_malloc(sizeof(*stmt));
	if (!stmt)
		return NULL;

	stmt->token = copy_tok();
	if (!stmt->token)
		return NULL;

	stmt->type = st;
	stmt->additional = NULL;
	return stmt;
}

int parse_return_statement(void)
{
	struct statement *ret = new_statement(SRETURN);
	if (!ret)
		return -1;

	if (next_token())
		return -1;

	/*
	TODO: We're skipping the expressions until we
	encounter a semicolon
	*/

	while (!cur_token_is(SEMICOLON)) {
		if (next_token())
			return -1;
	}

	list_add_tail(&ret->statement, &prg->statement_list);
	return 0;
}

int parse_let_statement(void)
{
	struct statement *stmt = new_statement(SLET);
	if (!stmt)
		return -1;

	int ret = expect_peek(IDENT);
	if (ret <= 0)
		return ret;

	struct let_statement *let = gc_malloc(sizeof(*let));
	
	let->ident = gc_malloc(sizeof(*let->ident));
	if (!let->ident)
		return -1;

	let->ident->token = copy_tok();
	if (!let->ident->token)
		return -1;

	size_t ident_len = strlen(let->ident->token->literal) + 1;
	let->ident->value = gc_malloc(ident_len);
	if (!let->ident->value)
		return -1;

	memcpy(let->ident->value, let->ident->token->literal, ident_len);

	ret = expect_peek(ASSIGN);
	if (ret <= 0)
		return ret;

	while (!cur_token_is(SEMICOLON)) {
		if (next_token())
			return -1;
	}

	stmt->additional = (void *)let;
	list_add_tail(&stmt->statement, &prg->statement_list);
	return 0;
}

enum expression_types {
	LOWEST,
	EQUALS,
	LESSGREATER,
	SUM,
	PRODUCT,
	PREFIX,
	CALL
};

struct expression *parse_expression(int precedence)
{
	struct prefix_parse_fn *prefix = lookup_prefix_parse_fn(p->cur_tok->type);
	if (!prefix)
		return NULL;

	return prefix->prefix_parse_fn();
}

int parse_expression_statement(void)
{
	struct statement *exp = new_statement(SEXPRESSION);
	if (!exp)
		return -1;

	if (peek_token_is(SEMICOLON)) {
		if (next_token())
			return -1;
	}

	return 0;
}

int parse_program(void)
{
	prg = gc_malloc(sizeof(*prg));
	if (!prg)
		return -1;

	INIT_LIST_HEAD(&prg->statement_list);
	INIT_LIST_HEAD(&prg->error_list);

	while (p->cur_tok->type != MEOF) {
		switch (p->cur_tok->type) {
		case LET:
			if (parse_let_statement())
				return -1;
			break;
		case RETURN:
			if (parse_return_statement())
				return -1;
			break;
		default:
			if (parse_expression_statement())
				return -1;
			break;
		}

		if (next_token())
			return -1;
	}
	return 0;
}

void parser_destroy(void)
{
	token_destroy(p->peek_tok);
	token_destroy(p->cur_tok);
	gc_free(p);
}
