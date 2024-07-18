//
// Created by RedNeath on 16/07/2024.
//

#include "abs.h"

operand *abs_invoke(operand **input, unsigned long arg_count) {
    char *stop;
    double value;

    switch(input[0]->type) {
        case TYPE_NUMBER:
            value = input[0]->number_value;
            break;

        case TYPE_BOOLEAN:
            value = input[0]->boolean_value;
            break;

        case TYPE_STRING:
            value = strtod(input[0]->string_value, &stop);
            break;
        
        case TYPE_DATE:
            value = input[0]->date_value;
            break;
    }

    // Will break if value isn't supported, but this should be caught at preprocessing step.
    operand *op = malloc(sizeof(operand));
    op->type = TYPE_NUMBER;
    op->number_value = fabs(value);

    return op;
}

unsigned short abs_preprocess(operand **input, unsigned long arg_count) {
    char *stop;
    if (arg_count != 1) return PP_INCORRECT_ARG_COUNT;

    if (input[0]->type == TYPE_SENTINEL) {
        return PP_INCORRECT_VALUE;
    }

    // Some strings can be interpreted as numbers
    if (input[0]->type == TYPE_STRING) {
        strtod(input[0]->string_value, &stop);
        if (*stop) return PP_INCORRECT_VALUE; // If the input hasn't been fully read, then this is not a number
    }
    
    return PP_OK;
}
