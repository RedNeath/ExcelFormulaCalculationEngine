//
// Created by RedNeath on 16/07/2024.
//

#include "pre_processor.h"

operation *preprocess(formula_context *context, formula_token *token) {
    operation *op;
    unsigned long child_count = get_child_count(token); // TODO

    operand **operands = resolve_operands(context, token, child_count);
    if (operands == NULL) return NULL;

    switch (token->type) {
        case TYPE_TOKEN_UNARY_OPERATOR:
            op = preprocess_unary_operator(token, operands);
            break;
        case TYPE_TOKEN_BINARY_OPERATOR:
            op = preprocess_binary_operator(token, operands);
            break;
        case TYPE_TOKEN_FUNCTION:
            op = preprocess_function(token, operands, child_count);
            break;
        
        default:
            return NULL;
    }

    return op;
}

operand **resolve_operands(formula_context *context, formula_token *token, unsigned long count) {
    if      (token->type == TYPE_TOKEN_UNARY_OPERATOR && count != 1) return NULL;
    else if (token->type == TYPE_TOKEN_BINARY_OPERATOR && count != 1) return NULL;

    operand **operands = malloc((count + 1) * sizeof(operand *));

    unsigned long i = 0;
    while (i < count) {
        // Theoretically, the corresponding formula_token should be either a variable, or a value.
        operand *child;
        
        switch (token->children[i]->type) {
            case TYPE_TOKEN_BOOLEAN:
                child = resolve_boolean_operand(token->children[i]);
                break;
            case TYPE_TOKEN_NUMBER:
                child = resolve_number_operand(token->children[i]);
                break;
            case TYPE_TOKEN_STRING:
                child = resolve_string_operand(token->children[i]);
                break;
            case TYPE_TOKEN_VARIABLE:
                child = resolve_variable_operand(context, token->children[i]);
                break;


            default: // Error case, not supposed to happen!
                free(operands);
                free(child);
                return NULL;
        }

        operands[i] = child;
        i++;
    }

    operands[count] = malloc(sizeof(operand));
    operands[count]->type = TYPE_SENTINEL;
    return operands;
}

operand *resolve_boolean_operand(formula_token *token) {
    operand *op = malloc(sizeof(operand));
    op->type = TYPE_BOOLEAN;
    op->boolean_value = !(strcmp(token->value, "TRUE") == 0);

    return op;
}

operand *resolve_number_operand(formula_token *token) {
    char *stop;

    operand *op = malloc(sizeof(operand));
    op->type = TYPE_NUMBER;
    op->number_value = strtod(token->value, &stop);
    
    return op;
}

operand *resolve_string_operand(formula_token *token) {
    // Need to copy the value again because the token might be freed
    size_t value_length = strlen(token->value);

    operand *op = malloc(sizeof(operand));
    op->type = TYPE_STRING;
    op->string_value = malloc((value_length + 1) * sizeof(char));
    memcpy(op->string_value, token->value, value_length);
    op->string_value[value_length] = '\0';

    return op;
}

operand *resolve_variable_operand(formula_context *context, formula_token *token) {
    formula_variable var = get_variable(context, token->value);

    operand *op = malloc(sizeof(operand));
    op->type = var.type;

    switch(op->type) {
        case TYPE_BOOLEAN:
            op->boolean_value = var.boolean_value->value;
            break;
        
        case TYPE_DATE:
            op->date_value = var.date_value->value;
            break;
        
        case TYPE_NUMBER:
            op->number_value = var.number_value->value;
            break;
        
        case TYPE_STRING:
            op->string_value = var.string_value->value;
    }

    // If the variable hasn't been found, the operand will have TYPE_SENTINEL as type and no value.
    return op;
}

operation *preprocess_unary_operator(formula_token *token, operand **operands) {
    // Only one operand, if it is wrong then the result is wrong too
    operation *op;

    if (operands[0]->type == TYPE_SENTINEL) {
        op = malloc(sizeof(operation));
        op->status = PP_UNKNOWN_NAME;
        return op;
    }

    if      (strcmp(token->value, "-") == 0) op = preprocess_negation(operands);
    else if (strcmp(token->value, "%") == 0) op = preprocess_percent(operands);

    return op;
}

operation *preprocess_negation(operand **operands) {
    operation *op = malloc(sizeof(operation));

    if (operands[0]->type == TYPE_STRING) {
        try_number_cast(operands[0]);
    }

    // Rechecking type because it may have changed
    if (
        operands[0]->type == TYPE_BOOLEAN ||
        operands[0]->type == TYPE_DATE ||
        operands[0]->type == TYPE_NUMBER
    ) {
        op->calculate = process_negation;
        op->operands = operands;
        op->status = PP_OK;

    } else {
        op->status = PP_INCORRECT_VALUE;
    }

    return op;
}

operation *preprocess_percent(operand **operands) {
    operation *op = malloc(sizeof(operation));

    if (operands[0]->type == TYPE_STRING) {
        try_number_cast(operands[0]);
    }

    // Rechecking type because it may have changed
    if (
        operands[0]->type == TYPE_BOOLEAN ||
        operands[0]->type == TYPE_DATE ||
        operands[0]->type == TYPE_NUMBER
    ) {
        op->calculate = process_percent;
        op->operands = operands;
        op->status = PP_OK;

    } else {
        op->status = PP_INCORRECT_VALUE;
    }

    return op;
}

operation *preprocess_binary_operator(formula_token *token, operand **operands) {
    // Exactly two operands, if it is wrong then the result is wrong too
    operation *op;

    if (operands[0]->type == TYPE_SENTINEL || operands[1]->type == TYPE_SENTINEL) {
        op = malloc(sizeof(operation));
        op->status = PP_UNKNOWN_NAME;
        return op;
    }

    // Later optimisation could use the return value from strcmp to proceed in a dichotomous way.
    if      (strcmp(token->value, "^") == 0) op = preprocess_power(operands);
    else if (strcmp(token->value, "*") == 0) op = preprocess_multiplication(operands);
    else if (strcmp(token->value, "/") == 0) op = preprocess_division(operands);
    else if (strcmp(token->value, "+") == 0) op = preprocess_addition(operands);
    else if (strcmp(token->value, "-") == 0) op = preprocess_subtraction(operands);
    else if (strcmp(token->value, "&") == 0) op = preprocess_concatenation(operands);
    else if (strcmp(token->value, "=") == 0) op = preprocess_equality(operands);
    else if (strcmp(token->value, ">") == 0) op = preprocess_strict_superiority(operands);
    else if (strcmp(token->value, "<") == 0) op = preprocess_strict_inferiority(operands);
    else if (strcmp(token->value, ">=") == 0) op = preprocess_superiority(operands);
    else if (strcmp(token->value, "<=") == 0) op = preprocess_inferiority(operands);
    else if (strcmp(token->value, "<>") == 0) op = preprocess_difference(operands);

    return op;
}

operation *preprocess_number_operator(calculation calculate, operand **operands) {
    operation *op = malloc(sizeof(operation));
    op->status = PP_OK;

    unsigned long i = 0;
    while (operands[i] != TYPE_SENTINEL && op->status == PP_OK) {
        if (operands[i]->type == TYPE_STRING) {
            try_number_cast(operands[i]);
        }

        if (
            operands[i]->type != TYPE_BOOLEAN &&
            operands[i]->type != TYPE_DATE &&
            operands[i]->type != TYPE_NUMBER
        ) {
            op->status = PP_INCORRECT_VALUE;
        }
        i++;
    }

    if (op->status == PP_OK) {
        op->calculate = calculate;
        op->operands = operands;
    }

    return op;
}

operation *preprocess_power(operand **operands) {
    return preprocess_number_operator(process_power, operands);
}

operation *preprocess_multiplication(operand **operands) {
    return preprocess_number_operator(process_multiplication, operands);
}

operation *preprocess_division(operand **operands) {
    return preprocess_number_operator(process_division, operands);
}

operation *preprocess_addition(operand **operands) {
    return preprocess_number_operator(process_addition, operands);
}

operation *preprocess_subtraction(operand **operands) {
    return preprocess_number_operator(process_subtraction, operands);
}

operation *preprocess_concatenation(operand **operands) {
    operation *op = malloc(sizeof(operation));
    op->status = PP_OK;
    
    unsigned long i = 0;
    while (operands[i]->type != TYPE_SENTINEL && op->status == PP_OK) {
        if (operands[i]->type != TYPE_STRING) {
            try_string_cast(operands[i]); // Should not fail, but who knows...
        }

        // Type may have been modified in the first if
        if (operands[i]->type != TYPE_STRING) {
            op->status = PP_INCORRECT_VALUE;
        }
        i++;
    }

    if (op->status == PP_OK) {
        op->calculate = process_concatenation;
        op->operands = operands;
    }

    return op;
}

operation *preprocess_equality(operand **operands) {
    operation *op = malloc(sizeof(operation));
    op->calculate = process_equality;
    op->operands = operands;
    op->status = PP_OK;
    return op;
}

operation *preprocess_strict_superiority(operand **operands) {
    operation *op = malloc(sizeof(operation));
    op->calculate = process_strict_superiority;
    op->operands = operands;
    op->status = PP_OK;
    return op;
}

operation *preprocess_strict_inferiority(operand **operands) {
    operation *op = malloc(sizeof(operation));
    op->calculate = process_strict_inferiority;
    op->operands = operands;
    op->status = PP_OK;
    return op;
}

operation *preprocess_superiority(operand **operands) {
    operation *op = malloc(sizeof(operation));
    op->calculate = process_superiority;
    op->operands = operands;
    op->status = PP_OK;
    return op;
}

operation *preprocess_inferiority(operand **operands) {
    operation *op = malloc(sizeof(operation));
    op->calculate = process_inferiority;
    op->operands = operands;
    op->status = PP_OK;
    return op;
}

operation *preprocess_difference(operand **operands) {
    operation *op = malloc(sizeof(operation));
    op->calculate = process_difference;
    op->operands = operands;
    op->status = PP_OK;
    return op;
}

operation *preprocess_function(formula_token *token, operand **operands, unsigned long child_count) {
    operation *op;
    excel_function *f = find_function(token->value); // No need to check: sentinel function is callable
    unsigned short status_code = f->preprocess(operands, child_count);
    if (status_code != PP_OK) {
        free(operands);
        operands = NULL;
    }

    op = malloc(sizeof(operation));
    op->calculate = f->invoke;
    op->operands = operands;
    op->status = status_code;
    return op;
}

void try_number_cast(operand *op) {
    char *stop;
    // Please use this only with string operands!
    double val = strtod(op->string_value, &stop);
    if (!*stop) {
        op->type = TYPE_NUMBER;
        op->number_value = val;
        free(op->string_value);
    }
}

void try_string_cast(operand *op) {
    unsigned short len;
    char *str;
    switch(op->type) {
        case TYPE_BOOLEAN:
            len = op->boolean_value? 4: 5;
            str = malloc((len + 1) * sizeof(char));
            memcpy(str, op->boolean_value? "TRUE": "FALSE", len);
            str[len] = '\0';

            op->string_value = str;
            op->type = TYPE_STRING;
            break;
        
        case TYPE_DATE: // Should actually depend on the representation...
            unsigned short max_long_length = 10;
            str = malloc((max_long_length + 1) * sizeof(char));
            sprintf(str, "%ld", op->date_value);

            op->string_value = str;
            op->type = TYPE_STRING;
            break;
        
        case TYPE_NUMBER:
            len = 32;
            str = malloc((len + 1) * sizeof(char));
            sprintf(str, "%.2f", op->number_value);

            op->string_value = str;
            op->type = TYPE_STRING;
            break;
    }
}

unsigned long get_child_count(formula_token *token) {
    unsigned long count = 0;
    while (token->children != NULL && token->children[count]->type != TYPE_SENTINEL) {
        count++;
    }

    return count;
}
