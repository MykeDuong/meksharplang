#ifndef PARSER_H
#define PARSER_H

#include "AST.h"
#include "lexer.h"

typedef struct PARSER_STRUCT {
	
	lexer_T* lexer;
	token_T* cur_token;
} parser_T;

parser_T* init_parser(lexer_T* lexer);

void parser_eat(parser_T* parser, int token_type);

// Return the AST Tree
AST_T* parser_parse(parser_T* parser);

// STATEMENTS
AST_T* parser_parse_statement(parser_T* parser);

AST_T* parser_parse_statements(parser_T* parser);


// MATHS
// Mathematical expressions - whole result
AST_T* parser_parse_expression(parser_T* parser);

// Mathematical expression - Multiplication
AST_T* parser_parse_factor(parser_T* parser);

// Mathematical expression - Addition
AST_T* parser_parse_term(parser_T* parser);


// FUNCTIONS
AST_T* parser_parse_func_call(parser_T* parser, char* token_value);


// VARIABLES
AST_T* parser_parse_var(parser_T* parser, char* token_value);

AST_T* parser_parse_var_def(parser_T* parser);


// STRINGS
AST_T* parser_parse_string(parser_T* parser);


// ID
AST_T* parser_parse_id(parser_T* parser);

AST_T* parser_parse_var_or_func(parser_T* parser);

#endif
