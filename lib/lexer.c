// #include "include/str.h"
// #include "include/lexer.h"
// #include <string.h>
// #include <stdio.h>
//
// struct lexer* new_lexer(struct str* input) 
// {
// 	struct lexer* l = (struct lexer*) malloc(sizeof(struct lexer));
// 	if (!l)
// 		goto err;
// 	memset(l, 0, sizeof(struct lexer));
// 	l->input = input;
// 	read_char(l);
// 	return l;
//
// err:
// 	printf("ERROR: could not allocate memory");
// 	exit(1);
// }
//
// void read_char(struct lexer* l)
// {
// 	if (l->read_position >= l->input->length)
// 		l->ch = 0;
// 	else
// 		l->ch = l->input->string[l->read_position];
//
// 	l->position = l->read_position;
// 	(l->read_position)++;
// }
