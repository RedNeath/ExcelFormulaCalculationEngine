//
// Created by RedNeath on 16/07/2024.
//

#include "pi.h"

// Don't need any of the parameters, but we still have to add them for standardisation
operand *pi_invoke(operand **input, unsigned long arg_count) {
    operand *op = malloc(sizeof(operand));
    op->type = TYPE_NUMBER;
    op->number_value = PI_VALUE;

    return op;
}

unsigned short pi_preprocess(operand **input, unsigned long arg_count) {
    if (arg_count != 0) return PP_INCORRECT_ARG_COUNT;
    
    return PP_OK;
}
