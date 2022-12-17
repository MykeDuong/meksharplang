#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/parser.h"

parser_T* init_parser(lexer_T* lexer) {
	parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));

	parser->lexer = lexer;
	parser->cur_token = lexer_get_next_token(lexer);
	
	return parser;
};

void parser_eat(parser_T* parser, int token_type) {
	if (parser->cur_token->type == token_type ) {
		parser->cur_token = lexer_get_next_token(parser->lexer);
	}

	else {
		printf(
			"Unexpected Token `%s`, with type %d",
			parser->cur_token->value,
			parser->cur_token->type
		);
		exit(1);
	}
}

// Return the AST Tree
AST_T* parser_parse(parser_T* parser) {
	return parser_parse_statements(parser);
}

// STATEMENTS
AST_T* parser_parse_statements(parser_T* parser) {
	AST_T* compound = init_ast(AST_COMPOUND);

	compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));

	AST_T* ast_statement = parser_parse_statement(parser);
	compound->compound_value[0] = ast_statement;

	while (parser->cur_token->type == TOKEN_SEMI) {
		// Eat (skip) the semicolon
		parser_eat(parser, TOKEN_SEMI);
		
		AST_T* ast_statement = parser_parse_statement(parser);
		compound->compound_size += 1;
		compound->compound_value = realloc(
			compound->compound_value,
			compound->compound_size * sizeof(struct AST_STRUCT)
		);
		compound->compound_value[compound->compound_size] = ast_statement;
	}

	return compound;
}

AST_T* parser_parse_statement(parser_T* parser) {
	switch (parser->cur_token->type) {
		case TOKEN_ID: return parser_parse_id(parser);
	}
}

// MATHS
// Mathematical expressions - whole result
AST_T* parser_parse_expression(parser_T* parser) {

}

// Mathematical expression - Multiplication
AST_T* parser_parse_factor(parser_T* parser) {

}

// Mathematical expression - Addition
AST_T* parser_parse_term(parser_T* parer) {

}

// FUNCTIONS
AST_T* parser_parse_func_call(parser_T* parser, char* token_value) {

}

// VARIABLES
AST_T* parser_parse_var(parser_T* parser, char* token_value) {
	AST_T* ast_var = init_ast(AST_VAR);
	ast_var->var_name = token_value;

	return ast_var;
}

AST_T* parser_parse_var_def(parser_T* parser) {
	parser_eat(parser, TOKEN_ID); // var
	
	char* var_def_name = parser->cur_token->value; // var name (id)
	parser_eat(parser, TOKEN_ID);

	parser_eat(parser, TOKEN_EQUALS); // Equal string
	
	AST_T* var_def_value = parser_parse_expression(parser);	// var value

	AST_T* var_def = init_ast(AST_VAR_DEF);

	var_def->var_def_name = var_def_name;
	var_def->var_def_value = var_def_value;

	return var_def;
}


// ID
AST_T* parser_parse_id(parser_T* parser) {
	if (strcmp(parser->cur_token->value, "var") == 0)	 {
		parser_parse_var_def(parser);
	} else {
		parser_parse_var_or_func(parser);
	}
}

AST_T* parser_parse_var_or_func(parser_T* parser) {
	char* token_value = parser->cur_token->value; // token value
	parser_eat(parser, TOKEN_ID);

	// Behave dynamically for var and func
	if (parser->cur_token->type == TOKEN_LPAR) {
		return parser_parse_func_call(parser, token_value);
	}
	else {
		return parser_parse_var(parser, token_value);
	}
}

AST_T* parser_parse_string(parser_T* parser) {

}

