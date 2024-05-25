#include "arena.h"
#include "token.h"

struct token* token_init(Arena* arena, Str* s, Token_Type tt)
{
	struct token* tok = arena_alloc(arena, sizeof(*tok));
	tok->literal = s;
	tok->type = tt;
	return tok;
}
