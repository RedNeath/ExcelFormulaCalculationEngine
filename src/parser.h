//
// Created by P15v on 03/06/2024.
//

#ifndef PARSER_H
#define PARSER_H

#include "context.h"

#define TYPE_NONE 0
#define TYPE_FORMULA 1
#define TYPE_EXPRESSION 2
#define TYPE_OPERAND 3
#define TYPE_FUNCTION 4
#define TYPE_FUNCTION_ARGS 5
#define TYPE_FUNTCTION_NAME 6
#define TYPE_PARENTHESIS 7
#define TYPE_BINARY_OPERATOR 8
#define TYPE_UNARY_OPERATOR 9
#define TYPE_SPECIAL_CHARACTER 10
#define TYPE_VARIABLE 11
#define TYPE_VALUE 12

typedef struct formula_token formula_token;

struct formula_token {
    char *value;
    unsigned short type;
    formula_token *children;
};

static const formula_token leaf_token = { NULL, 0, NULL };

extern formula_token *parse_formula(formula_context *context, char *input);
extern formula_token *parse_expression(formula_context *context, char *input);
extern formula_token *parse_parenthesis(formula_context *context, char *input);
extern formula_token *parse_negation(formula_context *context, char *input);
extern formula_token *parse_percent(formula_context *context, char *input);
extern formula_token *parse_power(formula_context *context, char *input);
extern formula_token *parse_multiplication_or_division(formula_context *context, char *input);
extern formula_token *parse_addition_or_substraction(formula_context *context, char *input);
extern formula_token *parse_concatenation(formula_context *context, char *input);
extern formula_token *parse_comparison(formula_context *context, char *input);
extern formula_token *parse_function(formula_context *context, char *input);
extern formula_token *parse_variable(formula_context *context, char *input);
extern formula_token *parse_value(formula_context *context, char *input);
extern formula_token *parse_string(formula_context *context, char *input);

#endif //PARSER_H
