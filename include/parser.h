#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "ast.h"

struct parser {
	struct token *cur_tok;
	struct token *peek_tok;
};

extern int new_parser(void);
extern int parse_program(void);
extern void parser_destroy(void);

extern struct parser *p;
extern struct program *prg;

#endif
