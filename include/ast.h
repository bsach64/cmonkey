#ifndef AST_H
#define AST_H

#include "list.h"

struct program {
	struct list_head statement_list;
};

#endif
