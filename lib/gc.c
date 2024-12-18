#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "gc.h"

static void collect_garabage(void)
{
	// printf("-- gc begin\n");
	// printf("-- gc end\n");
}

void *gc_malloc(size_t size)
{
	collect_garabage();
	return malloc(size);
}

void gc_free(void *ptr)
{
	free(ptr);
}
