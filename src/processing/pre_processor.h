//
// Created by RedNeath on 16/07/2024.
//
#pragma once
#ifndef PRE_PROCESSOR_H
#define PRE_PROCESSOR_H

#include <stdio.h>
#include <math.h>

// Pre-processing codes
#define PP_OK 0
#define PP_UNKNOWN_NAME 1
#define PP_INCORRECT_VALUE 2
#define PP_INCORRECT_ARG_COUNT 3

typedef struct operand operand;
typedef struct operation operation;
typedef operand *(*calculation)(operand **, unsigned long);

#include "../parser.h"
#include "../functions/functions_facade.h"
#include "processor.h"

struct operand {
    unsigned short type; // Using context types

    // Do not initialise the values you don't need!
    double number_value;
    bool boolean_value;
    char *string_value;
    long date_value;
};

struct operation {
    unsigned short status; // Use PP constants there to get an error up to the root.
    calculation calculate; 
    operand **operands;
};


/**
 * This function will ensure the data that the operation will be calculated from is correct.
 * 
 * It will first verify that the count of children is correct (not exceeding the max count, nor
 * receding the min count).
 * Then it will create the corresponding operand for each child (which means determining the value
 * type, and getting its value casted as the correct type).
 * And finally, it will call the token preprocessing function, according to the value of the given
 * token (calling the function's preprocessing function, or finding the appropriate operator's
 * preprocessing and calling it). This is the step will verify that the type of each child is
 * coherent with what the operator or function can work with.
 * 
 * @param formula_token *token The token to get ready for processing.
 * @return The `operation` ready to be calculated, or information about the error encountered when
 *         preprocessing the token and its children.
 */
extern operation *preprocess(formula_context *context, formula_token *token);

extern operand **resolve_operands(formula_context *context, formula_token *token, unsigned long count);
extern operand *resolve_boolean_operand(formula_token *token);
extern operand *resolve_number_operand(formula_token *token);
extern operand *resolve_string_operand(formula_token *token);
extern operand *resolve_variable_operand(formula_context *context, formula_token *token);

extern operation *preprocess_unary_operator(formula_token *token, operand **operands);
extern operation *preprocess_negation(operand **operands);
extern operation *preprocess_percent(operand **operands);
extern operation *preprocess_binary_operator(formula_token *token, operand **operands);
extern operation *preprocess_number_operator(calculation calculate, operand **operands);
extern operation *preprocess_power(operand **operands);
extern operation *preprocess_multiplication(operand **operands);
extern operation *preprocess_division(operand **operands);
extern operation *preprocess_addition(operand **operands);
extern operation *preprocess_subtraction(operand **operands);
extern operation *preprocess_concatenation(operand **operands);
extern operation *preprocess_equality(operand **operands);
extern operation *preprocess_strict_superiority(operand **operands);
extern operation *preprocess_strict_inferiority(operand **operands);
extern operation *preprocess_superiority(operand **operands);
extern operation *preprocess_inferiority(operand **operands);
extern operation *preprocess_difference(operand **operands);
extern operation *preprocess_function(formula_token *token, operand **operands, unsigned long child_count);

extern void try_number_cast(operand *op);
extern void try_string_cast(operand *op);

extern unsigned long get_child_count(formula_token *token);

#endif //PRE_PROCESSOR_H
