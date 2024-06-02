#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "arena.h"

Arena* arena_init(u64 initial_size)
{
	Arena* arena = malloc(sizeof(*arena));
	if (!arena)
		goto err;

	arena->buf = malloc(initial_size);
	if (!arena->buf)
		goto err;
	arena->buf_len = initial_size;
	arena->cur_offset = 0;
	return arena;
err:
	printf("ERROR: Could not allocate memory\n");
	exit(1);
}

void* arena_alloc(Arena* arena, u64 size)
{
	void* ptr;

	if (arena->cur_offset + size > arena->buf_len - 1) {
		return NULL;
	}
	if (arena->cur_offset == 0)
		ptr = &arena->buf[arena->cur_offset];
	else
		ptr = &arena->buf[arena->cur_offset + 1];
	arena->cur_offset += (size - 1);
	memset(ptr, 0, size);
	return ptr;
}

void arena_destroy(Arena* arena)
{
	free(arena->buf);
	free(arena);
}


Temp_Arena_Memory temp_area_memory_begin(Arena* arena)
{
	Temp_Arena_Memory temp = {
		.arena = arena,
		.cur_offset = arena->cur_offset
	};
	return temp;
}

void temp_area_memory_end(Temp_Arena_Memory temp)
{
	temp.arena->cur_offset = temp.cur_offset;
}
