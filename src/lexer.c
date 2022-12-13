#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "include/lexer.h"

lexer_T* init_lexer(char* contents) {
	lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return lexer;

};


void lexer_advance(lexer_T* lexer) {
	if (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	} 
}

// Return current token
token_T* lexer_advance_token(lexer_T* lexer, token_T* token) {
	lexer_advance(lexer);
	return token;
}

void lexer_skip_whitespace(lexer_T* lexer) {
	while (lexer->c == ' ' || lexer->c == 10) {
		lexer_advance(lexer);
	} 
}

token_T* lexer_get_next_token(lexer_T* lexer) {
	while (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
		
		if (lexer->c == ' ' || lexer->c == 10)
			lexer_skip_whitespace(lexer);
	
		if (isalnum(lexer->c))
			return lexer_collect_id(lexer);

		if (lexer->c == '"')
			return lexer_collect_string(lexer);

		switch (lexer->c) {
			case '=':
				return lexer_advance_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer)));
				break;
			case ';':
				return lexer_advance_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer)));
				break;
			case '(':
				return lexer_advance_token(lexer, init_token(TOKEN_LPAR, lexer_get_current_char_as_string(lexer)));
				break;
			case ')':
				return lexer_advance_token(lexer, init_token(TOKEN_RPAR, lexer_get_current_char_as_string(lexer)));
				break;
		}
		

		return (void*)0;
	}
}

token_T* lexer_collect_id(lexer_T* lexer) {
	char* str_val = calloc(1, sizeof(char));
	str_val[0] = '\0';


	while (isalnum(lexer->c)) {
		char* c = lexer_get_current_char_as_string(lexer);
		str_val = realloc(str_val, (strlen(str_val) + strlen(c) + 1 ) * sizeof(char));
		strcat(str_val, c);
		lexer_advance(lexer);
	}

	token_T* ret = init_token(TOKEN_ID, str_val);
	return ret;

}


token_T* lexer_collect_string(lexer_T* lexer) {
	
	lexer_advance(lexer);

	char* str_val = calloc(1, sizeof(char));
	str_val[0] = '\0';

	while (lexer->c != '"') {
		char* c = lexer_get_current_char_as_string(lexer);
		str_val = realloc(str_val, (strlen(str_val) + strlen(c) + 1 ) * sizeof(char));
		strcat(str_val, c);
		lexer_advance(lexer);
	}

	lexer_advance(lexer);

	return init_token(TOKEN_STRING, str_val);
}

char* lexer_get_current_char_as_string(lexer_T* lexer) {
	char* str = calloc(1, sizeof(char));

	str[0] = lexer->c;
	str[1] = '\0';

	return str;
}


