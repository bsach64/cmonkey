#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "ast.h"

struct parser {
	struct token *cur_tok;
	struct token *peek_tok;
};

struct indentifier {
	struct token *token;
	char *value;
};

struct let_statement {
	struct token *token;
	struct indentifier *ident;
	struct list_head statement;
};

struct return_statement {
	struct token *token;
	struct list_head statement;
};

extern int new_parser(void);
extern int parse_program(void);
extern void parser_destroy(void);
extern void let_statement_destroy(struct let_statement *let);
extern void return_statement_destroy(struct return_statement *ret);

extern struct parser *p;
extern struct program *prg;

#endif
