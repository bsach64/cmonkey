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

int new_parser(void)
{
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

int peak_token_is(token_type tt)
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
	if (peak_token_is(tt)) {
		if (next_token())
			return -1;
		return 1;
	}
	if (peek_error(tt))
		return -1;
	return 0;
}

int parse_return_statement(void)
{
	struct return_statement *ret = gc_malloc(sizeof(*ret));
	if (!ret)
		return -1;

	ret->token = copy_tok();
	if (!ret->token)
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
	return 0;
}

int parse_let_statement(void)
{
	struct let_statement *let = gc_malloc(sizeof(*let));
	if (!let)
		return -1;

	let->token = copy_tok();
	if (!let->token)
		return -1;

	int ret = expect_peek(IDENT);
	if (ret <= 0)
		return ret;
	
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

	list_add_tail(&let->statement, &prg->statement_list);
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
		default:
			break;
		}

		if (next_token())
			return -1;
	}
	return 0;
}
