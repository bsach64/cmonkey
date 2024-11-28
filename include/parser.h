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

extern struct parser *p;
extern struct program *prg;

#endif
