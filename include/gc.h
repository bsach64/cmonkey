#ifndef GC_H
#define GC_H

#include <stddef.h>

void *gc_malloc(size_t size);
void gc_free(void *ptr);

#endif // !GC_H
