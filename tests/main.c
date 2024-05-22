#include "arena.h"
#include <assert.h>

void test_arena()
{
	Arena* arena = arena_init();
	assert(arena->buf_len == 0);
	arena_alloc(arena, 1);
	assert(arena->buf_len == 1);
	arena_alloc(arena, 1);
	assert(arena->buf_len == 2);
	arena_destroy(arena);
}

int main(void)
{

}
