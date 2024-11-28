#include <stdio.h>

#include "ast.h"
#include "compiler.h"
#include "gc.h"
#include "list.h"

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
