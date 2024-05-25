#ifndef ARENA_H
#define ARENA_H

#include "types.h"

typedef struct {
	unsigned char* buf;
	u64 buf_len;
	u64 cur_offset;
} Arena;

Arena* arena_init(void);
void* arena_alloc(Arena* arena, u64 size);
void arena_destroy(Arena* arena);

typedef struct {
	Arena* arena;
	u64 cur_offset;
	u64 prev_offset;
} Temp_Arena_Memory;

Temp_Arena_Memory temp_area_memory_begin(Arena* arena);
void temp_area_memory_end(Temp_Arena_Memory temp);

#endif // !ARENA_H
