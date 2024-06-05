//
// Created by P15v on 03/06/2024.
//

#include "parser.h"

formula_token *parse_formula(formula_context *context, char *input) {
	if (*input != '=') {
		return &leaf_token;
	}

	input++;
	return parse_expression(context, input); // Potentially more than just one element in there!
}

formula_token *parse_expression(formula_context *context, char *input) {
    formula_token *token;
    if (strlen(input) == 0) return &leaf_token;

    token = parse_value(context, input);
    if (token->type != TYPE_NONE) return token;

    token = parse_function(context, input);
    if (token->type != TYPE_NONE) return token;

    token = parse_comparison(context, input);
    if (token->type != TYPE_NONE) return token;

    token = parse_concatenation(context, input);
    if (token->type != TYPE_NONE) return token;

    token = parse_addition_or_subtraction(context, input);
    if (token->type != TYPE_NONE) return token;

    token = parse_multiplication_or_division(context, input);
    if (token->type != TYPE_NONE) return token;

    token = parse_power(context, input);
    if (token->type != TYPE_NONE) return token;

    token = parse_percent(context, input);
    if (token->type != TYPE_NONE) return token;

    token = parse_negation(context, input);
    if (token->type != TYPE_NONE) return token;

    token = parse_parenthesis(context, input);
    if (token->type != TYPE_NONE) return token;

    // Variable evaluation last, because this might be the slowest to evaluate (especially if not a variable)
    token = parse_variable(context, input);
    if (token != TYPE_NONE) return token;

    return &leaf_token;
}

formula_token *parse_parenthesis(formula_context *context, char *input) {
    size_t input_length = strlen(input);
    if (input_length == 0) return &leaf_token;
    if (*input != '(' || input[input_length - 1] != ')') return &leaf_token;

    input++;

    char *expression = malloc((input_length - 1) * sizeof(char));
    memcpy(expression, input, input_length - 2);
    expression[input_length - 2] = '\0';

    return parse_expression(context, input);
}

formula_token *parse_negation(formula_context *context, char *input) {
    size_t input_length = strlen(input);
    if (input_length == 0) return &leaf_token;
    if (*input != '-') return &leaf_token;

    input++;
    formula_token *token = malloc(sizeof(formula_token));
    token->value = "-";
    token->type = TYPE_UNARY_OPERATOR;
    token->children = malloc(sizeof(formula_token *));
    token->children[0] = parse_expression(context, input);

    return token;
}

formula_token *parse_percent(formula_context *context, char *input) {
    size_t input_length = strlen(input);
    if (input_length == 0) return &leaf_token;
    if (input[input_length - 1] != '%') return &leaf_token;

    char *expression = malloc((input_length) * sizeof(char));
    memcpy(expression, input, input_length - 1);
    expression[input_length - 1] = '\0';
    formula_token *token = malloc(sizeof(formula_token));
    token->value = "%";
    token->type = TYPE_UNARY_OPERATOR;
    token->children = malloc(sizeof(formula_token *));
    token->children[0] = parse_expression(context, input);

    return token;
}

formula_token *parse_power(formula_context *context, char *input) {
    size_t input_length = strlen(input);
    if (input_length == 0) return &leaf_token;

    for (unsigned long i = input_length - 1; i > 0; i--) {
        // Note: i > 0 is not a mistake!
        if (input[i] != '^') continue;

        // Trying to parse the left side
        char *left = malloc((i + 1) * sizeof(char));
        memcpy(left, input, i);
        left[i] = '\0';
        formula_token *left_token = parse_expression(context, left);
        if (left_token->type == TYPE_NONE) {
            free(left);
            continue;
        }
        free(left);

        // Trying to parse the right side
        char *right = malloc((input_length - i) * sizeof(char));
        memcpy(right, input + i + 1, input_length - i - 1);
        right[input_length - i - 1] = '\0';
        formula_token *right_token = parse_expression(context, right);
        if (right_token->type == TYPE_NONE) {
            free(right);
            continue;
        }
        free(right);

        // Both sides are valid, can create and return the actual token
        formula_token *token = malloc(sizeof(formula_token));
        token->value = "^";
        token->type = TYPE_BINARY_OPERATOR;
        token->children = malloc(sizeof(formula_token *));
        token->children[0] = left_token;
        token->children[1] = right_token;

        return token;
    }

    return &leaf_token;
}
