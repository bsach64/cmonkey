#include <unistd.h>
#include <stdlib.h>

struct lexer {
	struct str* input;
	size_t position; // current position in input
	size_t read_position; // current reading position in input (after current char)
	char ch; // current char under examination
};

struct lexer* new_lexer(struct str* input);
void read_char(struct lexer* l);
