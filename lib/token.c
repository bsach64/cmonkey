#include <string.h>
#include "arena.h"
#include "token.h"

struct token* token_init(Arena* arena, const char* literal, token_type tt)
{
	struct token* tok = arena_alloc(arena, sizeof(struct token));
	str* s = arena_alloc(arena, sizeof(str));
	s->size = strlen(literal);
	s->str = arena_alloc(arena, s->size);
	memcpy(s->str, literal, s->size);
	tok->literal = s;
	tok->type = tt;
	return tok;
}
