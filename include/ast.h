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

enum statement_type {
	SLET,
	SRETURN,
	SEXPRESSION
};

struct statement {
	struct token *token;
	struct list_head statement;
	enum statement_type type;
	void *additional;
};

struct let_statement {
	struct indentifier *ident;
};

/* no additional fields required for return_statement, hence no struct */

/* for now */

enum expression_type {
	EINDENTIFIER
};

struct expression {
	struct token *token;
	enum expression_type type;
	void *additional;
};

extern void error_destroy(struct error *err);
extern void error_list_destroy(struct program *prg);
extern void program_destroy(struct program *prg);
extern void statement_destroy(struct statement *stmt);

#endif
