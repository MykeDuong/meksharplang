#ifndef AST_H
#define AST_H

typedef struct AST_STRUCT {
	enum {
		AST_VAR_DEF,
		AST_FUNC_CALL,
		AST_VAR,
		AST_STRING,
		AST_COMPOUND	// A list of multiple statements	
	} type;

	/* AST_VAR_DEF */
	char* var_def_name;
	struct AST_STRUCT* var_def_value;

	/* AST_VAR */
	char* var_name;

	/* AST_FUNC_CALL */
	char* func_call_name;
	struct AST_STRUCT** func_call_args;
	size_t func_call_args_size;

	/* AST_STRING */
	char* string_val;

	/* AST_COMPOUND*/
	struct AST_STRUCT** compound_value;
	size_t compound_size;

} AST_T;

AST_T* init_ast(int type);

#endif
