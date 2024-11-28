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

extern void error_destroy(struct error *err);
extern void error_list_destroy(struct program *prg);
extern void program_destroy(struct program *prg);

#endif
