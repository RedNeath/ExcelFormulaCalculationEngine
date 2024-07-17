//
// Created by RedNeath on 16/07/2024.
//

#ifndef PRE_PROCESSOR_H
#define PRE_PROCESSOR_H

#include "../parser.h"

// Pre-processing codes
#define PP_OK 0
#define PP_INCORRECT_VALUE 1

typedef struct operand operand;
typedef struct operation operation;
typedef operand *(*calculation)(operand *input);

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
    operand *operands;
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
extern operation preprocess(formula_token *token);

#endif //PRE_PROCESSOR_H
