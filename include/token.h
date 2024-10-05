#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
	MILLEGAL,
	MEOF,
	IDENT,
	INT,
	ASSIGN,
	PLUS,
	MINUS,
	BANG,
	ASTERISK,
	SLASH,
	LT,
	GT,
	COMMA,
	SEMICOLON,
	LPAREN,
	RPAREN,
	LBRACE,
	RBRACE,
	FUNCTION,
	LET,
	TRUE,
	FALSE,
	IF,
	ELSE,
	RETURN,
	EQ,
	NOT_EQ
} token_type; 

struct token {
	token_type type;
	char* literal;
};

extern struct token *tok;

int token_char_init(char s, token_type tt);
int token_str_init(const char* s, token_type tt);
void token_destroy(void);
int init_keywords(void);
void free_keywords(void);
token_type lookup_indent(char* indentifier);

#endif // !TOKEN_H
