#include <stddef.h>
#include <stdlib.h>

#include "gc.h"

// might be useful when I later implement some sort of GC
void *gc_malloc(size_t size)
{
	return malloc(size);
}

void gc_free(void *ptr)
{
	free(ptr);
}
