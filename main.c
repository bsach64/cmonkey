#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "lexer.h"
#include "token.h"

int main(void)
{
	char* line = NULL;
	if (init_keywords())
		return -1;
	size_t size = 0;

	printf("Hello! This is the Monkey Programming language!\n");
	printf("Feel free to type commands!\n");
	while (1) {
		printf(">> ");
		getline(&line, &size, stdin);
		if (lexer_init(line))
			return -1;
		if (lexer_next_token())
			return -1;
		while (tok->type != MEOF) {
			print_token();
			token_destroy(tok);
			if (lexer_next_token())
				return -1;
		}
		lexer_destroy();
		free(line);
		line = NULL;
		size = 0;
	}
	free_keywords();
}
