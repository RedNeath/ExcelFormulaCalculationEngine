//
// Created by RedNeath on 16/07/2024.
//

#include "abs.h"

operand *abs_invoke(operand *input) {
    char *stop;
    double value;

    switch(input->type) {
        case TYPE_NUMBER:
            value = input->number_value;
            break;

        case TYPE_BOOLEAN:
            value = input->boolean_value;
            break;

        case TYPE_STRING:
            value = strtod(input->string_value, *stop);
            break;
        
        case TYPE_DATE:
            value = input->date_value;
            break;
    }

    // Will break if value isn't supported, but this should be caught at preprocessing step.
    operand *op = malloc(sizeof(operand));
    op->type = TYPE_NUMBER;
    op->number_value = fabs(value);

    return op;
}

unsigned short abs_preprocess(operand *input) {
    char *stop;

    if (input->type == TYPE_SENTINEL) {
        return PP_INCORRECT_VALUE;
    }

    // Some strings can be interpreted as numbers
    if (input->type == TYPE_STRING) {
        strtod(input->string_value, &stop);
        if (*stop) return PP_INCORRECT_VALUE; // If the input hasn't been fully read, then this is not a number
    }
    
    return PP_OK;
}
