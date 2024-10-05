#ifndef LEXER_H
#define LEXER_H

#include <stdlib.h>

struct lexer {
	char* input;
	size_t position;
	size_t read_position;
	size_t input_len;
	char ch;
};

extern struct lexer *l;
int lexer_init(const char* input);
void lexer_read_char(void);
char lexer_peek_char(void);
int lexer_next_token(void);
char* lexer_read_indentifier(void);
char* lexer_read_number(void);
void lexer_destroy(void);

#endif // !LEXER_H
