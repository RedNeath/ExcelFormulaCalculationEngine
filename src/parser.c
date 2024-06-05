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

    token = parse_addition_or_substraction(context, input);
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
    if (*input != '(' || input[strlen(input) - 1] != ')') return &leaf_token;

    input++;
    input[strlen(input) - 1] = '\0';

    return parse_expression(context, input);
}

formula_token *parse_negation(formula_context *context, char *input) {
    if (*input != '-') return &leaf_token;

    input++;
    formula_token *token = malloc(sizeof(formula_token));
    token->value = "-";
    token->type = TYPE_UNARY_OPERATOR;
    token->children = parse_expression(context, input);

    return token;
}

formula_token *parse_percent(formula_context *context, char *input) {
    if (input[strlen(input) - 1] != '%') return &leaf_token;

    input[strlen(input) -1] = '\0';
    formula_token *token = malloc(sizeof(formula_token));
    token->value = "%";
    token->type = TYPE_UNARY_OPERATOR;
    token->children = parse_expression(context, input);

    return token;
}

formula_token *parse_power(formula_context *context, char *input) {

}
