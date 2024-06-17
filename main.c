#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "lexer.h"
#include "token.h"

int main(void)
{
	char* line = NULL;
	size_t size = 0;

	printf("Hello! This is the Monkey Programming language!\n");
	printf("Feel free to type commands!\n");
	while (1) {
		printf(">> ");
		getline(&line, &size, stdin);
		struct lexer* l = lexer_init(line);
		struct token* t = lexer_next_token(l);
		while (t->type != MEOF) {
			print_token(t);
			token_destroy(t);
			t = lexer_next_token(l);
		}
		lexer_destroy(l);
		free(line);
		line = NULL;
		size = 0;
	}
}
