#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>

typedef struct {
	unsigned char* buf;
	size_t buf_len;
	size_t cur_offset;
} Arena;

Arena* arena_init(void);
void* arena_alloc(Arena* arena, size_t size);
void arena_destroy(Arena* arena);

typedef struct {
	Arena* arena;
	size_t cur_offset;
	size_t prev_offset;
} Temp_Arena_Memory;

Temp_Arena_Memory temp_area_memory_begin(Arena* arena);
void temp_area_memory_end(Temp_Arena_Memory temp);

#endif // !ARENA_H
