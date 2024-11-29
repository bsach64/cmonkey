#ifndef AST_H
#define AST_H

#include "list.h"

struct program {
	struct list_head statement_list;
	struct list_head error_list;
};

struct error {
	char* error_msg;
	struct list_head next;
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

extern void error_destroy(struct error *err);
extern void error_list_destroy(struct program *prg);
extern void program_destroy(struct program *prg);
extern void let_statement_destroy(struct let_statement *let);
extern void return_statement_destroy(struct return_statement *ret);

#endif
