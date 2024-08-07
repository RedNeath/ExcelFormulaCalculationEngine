//
// Created by P15v on 03/06/2024.
//

#ifndef PARSER_H
#define PARSER_H

#include "context.h"

#define TYPE_TOKEN_NONE 0
#define TYPE_TOKEN_FORMULA 1
#define TYPE_TOKEN_EXPRESSION 2
#define TYPE_TOKEN_OPERAND 3
#define TYPE_TOKEN_FUNCTION 4
#define TYPE_TOKEN_FUNCTION_ARGS 5
#define TYPE_TOKEN_PARENTHESIS 6
#define TYPE_TOKEN_BINARY_OPERATOR 7
#define TYPE_TOKEN_UNARY_OPERATOR 8
#define TYPE_TOKEN_SPECIAL_CHARACTER 9
#define TYPE_TOKEN_BOOLEAN 10
#define TYPE_TOKEN_NUMBER 11
#define TYPE_TOKEN_STRING 12
#define TYPE_TOKEN_VARIABLE 13

typedef struct formula_token formula_token;

struct formula_token {
    char *value;
    unsigned short type;
    formula_token **children;
};

extern formula_token *leaf_token();
extern formula_token *parse_formula(formula_context *context, char *input);
extern formula_token *parse_expression(formula_context *context, char *input);
extern formula_token *parse_parenthesis(formula_context *context, char *input);
extern formula_token *parse_negation(formula_context *context, char *input);
extern formula_token *parse_percent(formula_context *context, char *input);
extern formula_token *parse_power(formula_context *context, char *input);
extern formula_token *parse_multiplication_or_division(formula_context *context, char *input);
extern formula_token *parse_addition_or_subtraction(formula_context *context, char *input);
extern formula_token *parse_concatenation(formula_context *context, char *input);
extern formula_token *parse_comparison(formula_context *context, char *input);
extern formula_token *parse_function(formula_context *context, char *input);
extern formula_token *parse_variable(formula_context *context, char *input);
extern formula_token *parse_value(char *input);
extern formula_token *parse_string(char *input);
extern formula_token *parse_boolean(char *input);
extern formula_token *parse_number(char *input);
extern formula_token **parse_function_args(formula_context *context, char *input);

extern void free_token(formula_token *root_token);

#endif //PARSER_H
