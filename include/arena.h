#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>

typedef struct {
	unsigned char* buf;
	size_t buf_len;
	size_t cur_offset;
} Arena;

Arena* arena_init();
void* arena_alloc(Arena* arena, size_t size);
void arena_destroy(Arena* arena);

#endif // !ARENA_H
