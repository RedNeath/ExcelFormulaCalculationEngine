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
#define TYPE_OPERATOR 7
#define TYPE_SPECIAL_CHARACTER 8
#define TYPE_VARIABLE 9
#define TYPE_VALUE 10

typedef struct formula_token formula_token;

struct formula_token {
    char *value;
    unsigned short type;
    formula_token *child;
};

extern formula_token parse_formula(formula_context *context, char *input);
extern formula_token parse_expression(formula_context *context, char *input);
extern formula_token parse_operand(formula_context *context, char *input);
extern formula_token parse_function(formula_context *context, char *input);
extern formula_token parse_function_args(formula_context *context, char *input);
extern formula_token parse_function_name(formula_context *context, char *input);
extern formula_token parse_operator(formula_context *context, char *input);
extern formula_token parse_special_character(formula_context *context, char *input);
extern formula_token parse_variable(formula_context *context, char *input);
extern formula_token parse_value(formula_context *context, char *input);

#endif //PARSER_H
