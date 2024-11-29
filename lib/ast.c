#include <math.h>
#include <stdio.h>

#include "ast.h"
#include "compiler.h"
#include "gc.h"
#include "list.h"
#include "token.h"

void program_destroy(struct program *prg)
{
	if (!list_empty(&prg->error_list)) {
		error_list_destroy(prg);
	}

	gc_free(prg);
}

void error_list_destroy(struct program *prg)
{
	struct error *err;
	if (list_empty(&prg->error_list))
		return;

	struct list_head *end = prg->error_list.prev;
	struct list_head *start = &prg->error_list;
	while (end != start) {
		err = container_of(end, struct error, next);
		end = end->prev;
		error_destroy(err);
	}
	start = NULL;
}

void error_destroy(struct error *err)
{
	err->next.next = NULL;
	err->next.prev = NULL;
	gc_free(err->error_msg);
	gc_free(err);
}

void statement_destroy(struct statement *stmt)
{
	stmt->statement.prev = NULL;
	stmt->statement.next = NULL;
	token_destroy(stmt->token);
	if (stmt->type == SLET) {
		struct let_statement *let = (struct let_statement *)stmt->additional;
		token_destroy(let->ident->token);
		gc_free(let->ident->value);
		gc_free(let->ident);
		gc_free(let);
	}
	gc_free(stmt);
}
