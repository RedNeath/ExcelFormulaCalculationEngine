//
// Created by P15v on 03/06/2024.
//

#include "parser.h"

formula_token *parse_formula(formula_context *context, char *input) {
	if (*input != '=') {
		return NULL;
	}

	input++;
	return parse_expression(context, input); // Potentially more than just one element in there!
}

formula_token *parse_expression(formula_context *context, char *input) {
    formula_token *token;
    if (strlen(input) == 0) return NULL;

    token = parse_comparison(context, input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    token = parse_concatenation(context, input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    token = parse_addition_or_subtraction(context, input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    token = parse_multiplication_or_division(context, input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    token = parse_power(context, input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    token = parse_percent(context, input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    token = parse_negation(context, input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    token = parse_parenthesis(context, input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    token = parse_function(context, input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    token = parse_value(input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    // Variable evaluation last, because this might be the slowest to evaluate (especially if not a variable)
    token = parse_variable(context, input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    return NULL;
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
    token->type = TYPE_TOKEN_UNARY_OPERATOR;
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
    token->type = TYPE_TOKEN_UNARY_OPERATOR;
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
        if (left_token->type == TYPE_TOKEN_NONE) {
            free(left);
            continue;
        }
        free(left);

        // Trying to parse the right side
        char *right = malloc((input_length - i) * sizeof(char));
        memcpy(right, input + i + 1, input_length - i - 1);
        right[input_length - i - 1] = '\0';
        formula_token *right_token = parse_expression(context, right);
        if (right_token->type == TYPE_TOKEN_NONE) {
            free(right);
            free_token(left_token); // Must free OK left token!
            continue;
        }
        free(right);

        // Both sides are valid, can create and return the actual token
        formula_token *token = malloc(sizeof(formula_token));
        token->value = "^";
        token->type = TYPE_TOKEN_BINARY_OPERATOR;
        token->children = malloc(sizeof(formula_token *));
        token->children[0] = left_token;
        token->children[1] = right_token;

        return token;
    }

    return &leaf_token;
}

formula_token *parse_multiplication_or_division(formula_context *context, char *input) {
    size_t input_length = strlen(input);
    if (input_length == 0) return &leaf_token;

    for (unsigned long i = input_length - 1; i > 0; i--) {
        // Note: i > 0 is not a mistake!
        if (input[i] != '*' && input[i] != '/') continue;

        // Trying to parse the left side
        char *left = malloc((i + 1) * sizeof(char));
        memcpy(left, input, i);
        left[i] = '\0';
        formula_token *left_token = parse_expression(context, left);
        if (left_token->type == TYPE_TOKEN_NONE) {
            free(left);
            continue;
        }
        free(left);

        // Trying to parse the right side
        char *right = malloc((input_length - i) * sizeof(char));
        memcpy(right, input + i + 1, input_length - i - 1);
        right[input_length - i - 1] = '\0';
        formula_token *right_token = parse_expression(context, right);
        if (right_token->type == TYPE_TOKEN_NONE) {
            free(right);
            free_token(left_token); // Must free OK left token!
            continue;
        }
        free(right);

        // Both sides are valid, can create and return the actual token
        formula_token *token = malloc(sizeof(formula_token));
        token->value = input[i] == '*'? "*": "/";
        token->type = TYPE_TOKEN_BINARY_OPERATOR;
        token->children = malloc(sizeof(formula_token *));
        token->children[0] = left_token;
        token->children[1] = right_token;

        return token;
    }

    return &leaf_token;
}

formula_token *parse_addition_or_subtraction(formula_context *context, char *input) {
    size_t input_length = strlen(input);
    if (input_length == 0) return &leaf_token;

    for (unsigned long i = input_length - 1; i > 0; i--) {
        // Note: i > 0 is not a mistake!
        if (input[i] != '+' && input[i] != '-') continue;

        // Trying to parse the left side
        char *left = malloc((i + 1) * sizeof(char));
        memcpy(left, input, i);
        left[i] = '\0';
        formula_token *left_token = parse_expression(context, left);
        if (left_token->type == TYPE_TOKEN_NONE) {
            free(left);
            continue;
        }
        free(left);

        // Trying to parse the right side
        char *right = malloc((input_length - i) * sizeof(char));
        memcpy(right, input + i + 1, input_length - i - 1);
        right[input_length - i - 1] = '\0';
        formula_token *right_token = parse_expression(context, right);
        if (right_token->type == TYPE_TOKEN_NONE) {
            free(right);
            free_token(left_token); // Must free OK left token!
            continue;
        }
        free(right);

        // Both sides are valid, can create and return the actual token
        formula_token *token = malloc(sizeof(formula_token));
        token->value = input[i] == '+'? "+": "-";
        token->type = TYPE_TOKEN_BINARY_OPERATOR;
        token->children = malloc(sizeof(formula_token *));
        token->children[0] = left_token;
        token->children[1] = right_token;

        return token;
    }

    return &leaf_token;
}

formula_token *parse_concatenation(formula_context *context, char *input) {
    size_t input_length = strlen(input);
    if (input_length == 0) return &leaf_token;

    for (unsigned long i = input_length - 1; i > 0; i--) {
        // Note: i > 0 is not a mistake!
        if (input[i] != '&') continue;

        // Trying to parse the left side
        char *left = malloc((i + 1) * sizeof(char));
        memcpy(left, input, i);
        left[i] = '\0';
        formula_token *left_token = parse_expression(context, left);
        if (left_token->type == TYPE_TOKEN_NONE) {
            free(left);
            continue;
        }
        free(left);

        // Trying to parse the right side
        char *right = malloc((input_length - i) * sizeof(char));
        memcpy(right, input + i + 1, input_length - i - 1);
        right[input_length - i - 1] = '\0';
        formula_token *right_token = parse_expression(context, right);
        if (right_token->type == TYPE_TOKEN_NONE) {
            free(right);
            free_token(left_token); // Must free OK left token!
            continue;
        }
        free(right);

        // Both sides are valid, can create and return the actual token
        formula_token *token = malloc(sizeof(formula_token));
        token->value = "&";
        token->type = TYPE_TOKEN_BINARY_OPERATOR;
        token->children = malloc(sizeof(formula_token *));
        token->children[0] = left_token;
        token->children[1] = right_token;

        return token;
    }

    return &leaf_token;
}

formula_token *parse_comparison(formula_context *context, char *input) {
    size_t input_length = strlen(input);
    if (input_length == 0) return &leaf_token;

    // Needs optimisation!!
    for (unsigned long i = input_length - 1; i > 1; i--) {
        // Note: i > 1 is not a mistake!
        if (!(input[i] == '=' && (input[i - 1] == '>' || input[i - 1] == '<')) &&
            !(input[i] == '>' && input[i - 1] == '<')
        ) continue;

        // Trying to parse the left side
        char *left = malloc(i * sizeof(char));
        memcpy(left, input, i - 1);
        left[i - 1] = '\0';
        formula_token *left_token = parse_expression(context, left);
        if (left_token->type == TYPE_TOKEN_NONE) {
            free(left);
            continue;
        }
        free(left);

        // Trying to parse the right side
        char *right = malloc((input_length - i) * sizeof(char));
        memcpy(right, input + i + 1, input_length - i - 1);
        right[input_length - i - 1] = '\0';
        formula_token *right_token = parse_expression(context, right);
        if (right_token->type == TYPE_TOKEN_NONE) {
            free(right);
            free_token(left_token); // Must free OK left token!
            continue;
        }
        free(right);

        // Both sides are valid, can create and return the actual token
        formula_token *token = malloc(sizeof(formula_token));
        token->value = input[i] == '>'? "<>":
            input[i - 1] == '>'? ">=": "<=";
        token->type = TYPE_TOKEN_BINARY_OPERATOR;
        token->children = malloc(sizeof(formula_token *));
        token->children[0] = left_token;
        token->children[1] = right_token;

        return token;
    }

    for (unsigned long i = input_length - 1; i > 0; i--) {
        // Note: i > 0 is not a mistake!
        if (input[i] != '=' && input[i] != '<'&& input[i] != '>') continue;

        // Trying to parse the left side
        char *left = malloc((i + 1) * sizeof(char));
        memcpy(left, input, i);
        left[i] = '\0';
        formula_token *left_token = parse_expression(context, left);
        if (left_token->type == TYPE_TOKEN_NONE) {
            free(left);
            continue;
        }
        free(left);

        // Trying to parse the right side
        char *right = malloc((input_length - i) * sizeof(char));
        memcpy(right, input + i + 1, input_length - i - 1);
        right[input_length - i - 1] = '\0';
        formula_token *right_token = parse_expression(context, right);
        if (right_token->type == TYPE_TOKEN_NONE) {
            free(right);
            free_token(left_token); // Must free OK left token!
            continue;
        }
        free(right);

        // Both sides are valid, can create and return the actual token
        formula_token *token = malloc(sizeof(formula_token));
        token->value = input[i] == '+'? "+": "-";
        token->type = TYPE_TOKEN_BINARY_OPERATOR;
        token->children = malloc(sizeof(formula_token *));
        token->children[0] = left_token;
        token->children[1] = right_token;

        return token;
    }

    return &leaf_token;
}

formula_token *parse_function(formula_context *context, char *input) {
    size_t input_length = strlen(input);
    if (input_length == 0) return &leaf_token;
    if (input[input_length - 1] != ')') return &leaf_token;

    // Getting the function's name
    unsigned long first_parenthesis = 1; // Name length must be at least 1!
    for (; first_parenthesis < (input_length - 1); first_parenthesis++) {
        if (input[first_parenthesis] == '(') break;
    }
    if (input[first_parenthesis] != '(') return &leaf_token;

    char *arguments = malloc((input_length - first_parenthesis - 1) * sizeof(char));
    memcpy(arguments, (input + first_parenthesis + 1), (input_length - first_parenthesis - 2));
    arguments[input_length - first_parenthesis - 2] = '\0';
    formula_token **children = parse_function_args(context, arguments);
    if (children == NULL) return &leaf_token;

    char *name = malloc((first_parenthesis + 1) * sizeof(char));
    memcpy(name, input, first_parenthesis);
    name[first_parenthesis] = '\0';

    formula_token *token = malloc(sizeof(formula_token));
    token->type = TYPE_TOKEN_FUNCTION;
    token->value = name;
    token->children = children;

    return token;
}

formula_token *parse_variable(formula_context *context, char *input) {
    size_t input_length = strlen(input);
    if (input_length == 0) return &leaf_token;

    // I don't like that, highly inefficient when there are lots of variables, plus we will have to try to find it
    // once again later on...
    formula_variable variable = get_variable(context, input);
    if (variable.type == TYPE_SENTINEL) return &leaf_token;

    char *name = malloc((input_length) * sizeof(char));
    memcpy(name, input, input_length - 1);
    name[input_length - 1] = '\0';

    formula_token *token = malloc(sizeof(formula_token));
    token->type = TYPE_TOKEN_VARIABLE;
    token->value = name;
    token->children = NULL;

    return token;
}

formula_token *parse_value(char *input) {
    formula_token *token;
    if (strlen(input) == 0) return &leaf_token;

    token = parse_string(input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    token = parse_boolean(input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    token = parse_number(input);
    if (token->type != TYPE_TOKEN_NONE) return token;

    return &leaf_token;
}

formula_token *parse_string(char *input) {
    size_t input_length = strlen(input);
    if (input_length == 0) return &leaf_token;
    if (*input != '"' || input[input_length - 1] != '"') return &leaf_token;

    input++;

    for (unsigned long i; i < input_length - 2; i++) {
        if (input[i] == '"' && (input[i + 1] != '"' || i + 1 >= input_length - 2)) return &leaf_token;

        // Handling escaped double quotes:
        else if (input[i] == '"' && input[i + 1] == '"') i++; // Jumping next iteration
    }

    char *value = malloc((input_length - 1) * sizeof(char));
    memcpy(value, input, input_length - 2);
    value[input_length - 2] = '\0';

    formula_token *token = malloc(sizeof(formula_token));
    token->value = value;
    token->type = TYPE_TOKEN_STRING;
    token->children = NULL;

    return token;
}

formula_token *parse_boolean(char *input) {
    int isTrue = strcmp(input, "TRUE") == 0;
    int isFalse = strcmp(input, "FALSE") == 0;
    if (!isTrue && !isFalse) return &leaf_token;

    formula_token *token = malloc(sizeof(formula_token));
    token->value = isTrue? "TRUE": "FALSE";
    token->type = TYPE_TOKEN_BOOLEAN;
    token->children = NULL;

    return token;
}

formula_token *parse_number(char *input) {
    size_t input_length = strlen(input);
    char *stop;
    double number;
    char *number_copy;

    number = strtod(input, &stop);
    if (*stop) return &leaf_token; // If the input hasn't been fully read, then this is not a number

    number_copy = malloc((input_length + 1) * sizeof(char));
    memcpy(number_copy, input, input_length);
    number_copy[input_length] = '\0';

    formula_token *token = malloc(sizeof(formula_token));
    token->value = number_copy;
    token->type = TYPE_TOKEN_NUMBER;
    token->children = NULL;

    return token;
}

formula_token **parse_function_args(formula_context *context, char *input) {
    // Note: for the time being, as we do not handle locales yet, the args separator will be the comma, which is the
    // default for english languages.
    formula_token **arguments;
    size_t input_size = strlen(input);
    unsigned long arg_count = input_size == 0? 0: 1;
    unsigned long arg_length;
    unsigned long level = 0; // ignore separators when in another function!
    char *argument;

    // Counting the number of args to allocate the memory
    for (unsigned long i = 0; i < input_size; i++) {
        // Theoretically, the level shouldn't be capable of going below zero. However, there is no guarantee that we are
        // really trying to parse the arguments of a function when we get there, so it could well be possible that we
        // meet a closing parenthesis in our input before we meet an opening one.
        // In this scenario, the input is undeniably incorrect, so we stop the treatment there.
        if (input[i] == ')' && level == 0) return NULL;
        if (input[i] == ',' && level == 0) arg_count++;

        if (input[i] == '(') level++;
        if (input[i] == ')') level --;
    }
    // If our level isn't back down to 0, the input is incorrect
    if (level > 0) return NULL;

    arguments = malloc((arg_count + 1) * sizeof(formula_token *));
    if (input_size == 0) {
        arguments[0] = &leaf_token;
        return arguments; // No arguments
    }

    for (unsigned long i = 0; i < arg_count; i++) {
        arg_length = 0;

        while (*input != '\0') {
            if (*input == '(') level++;
            if (*input == ')') level--;

            if (*input == ',' && level == 0) break;

            input++;
            arg_length++;
        }

        argument = malloc((arg_length + 1) * sizeof(char));
        memcpy(argument, (input - arg_length), arg_length);
        argument[arg_length] = '\0';

        // Search down for an expression
        formula_token *arg_token = parse_expression(context, argument);
        if (arg_token == NULL) {
            for (unsigned long j; j < i; j++) free_token(arguments[j]);
            return NULL;
        }
        arguments[i] = arg_token;
    }

    return arguments;
}

void free_token(formula_token *root_token) {
    unsigned long i = 0;
    while (root_token->children[i]->type != TYPE_TOKEN_NONE) {
        free_token(root_token->children[i]);
    }

    free(root_token->value);
    free(root_token);
}
