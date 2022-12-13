#include <stdio.h> 

#include "include/lexer.h"

int main(int argc, char* argv[]) {
  lexer_T* lexer = init_lexer(
		"var name = \"Minh Duong\";\n"
		"print(name);\n"
	); 

	token_T* token = lexer_get_next_token(lexer);

	while (token != (void*)0) {
		printf("TOKEN(%d, %s)\n", token->type, token->value);
		token = lexer_get_next_token(lexer);	
	}
	
	return 0;

}
