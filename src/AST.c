#include <stdlib.h>
#include "include/AST.h"

AST_T* init_ast(int type) {
	AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
	ast->type = type;

	/* AST_VAR_DEF */
	ast->var_def_name = (void*) 0;
	ast->var_def_value = (void*) 0;

	/* AST_VAR */
	ast->var_name = (void*) 0;

	/* AST_FUNC_CALL */
	ast->func_call_name = (void*) 0;
	ast->func_call_args = (void*) 0;
	ast->func_call_args_size = 0;

	/* AST_STRING */
	ast->string_val = (void*) 0;

	/* AST_COMPOUND */
	ast->compound_value = (void*) 0;
	ast->compound_size = 0;

	return ast;
}


