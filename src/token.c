#include "include/token.h"
#include "stdlib.h"
#include "stdio.h"

token_T* init_token(int type, char* value) {
	token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
	token->type = type;
	token->value = value;
	//printf("%d\n", type);
	//printf("%s\n", value);
	//printf("%d, %s", token->type, token->value);	
	return token;
}
