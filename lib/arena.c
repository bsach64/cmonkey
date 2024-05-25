#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "arena.h"

Arena* arena_init(void)
{
	Arena* arena = malloc(sizeof(Arena));
	if (arena == NULL)
		goto err;

	arena->buf = NULL;
	arena->buf_len = 0;
	arena->cur_offset = 0;
	return arena;
err:
	printf("ERROR: Could not allocate memory\n");
	exit(1);
}

void* arena_alloc(Arena* arena, u64 size)
{
	if (arena->buf_len < arena->cur_offset + size) {
		if (arena->buf_len * 2 > arena->cur_offset + size)
			arena->buf_len *= 2;
		else
			arena->buf_len += size;
		unsigned char* new_buf = realloc(arena->buf, arena->buf_len);
		if (!new_buf)
			goto err;
		arena->buf = new_buf;
	}
	void* ptr = &arena->buf[arena->cur_offset];
	arena->cur_offset += size;
	memset(ptr, 0, size);
	return ptr;
err:
	printf("ERROR: Could not reallocate memory\n");
	arena_destroy(arena);
	exit(1);
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
