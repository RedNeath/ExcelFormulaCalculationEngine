//
// Created by RedNeath on 31/05/24.
//

#ifndef EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H
#define EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H

#include "../context.h"

#define FUNCTION_NONE 0
#define FUNCTION_COUNT 1

/* Import the functions */
#include "mathematics_and_trigonometry/abs.h"

typedef struct excel_function excel_function;
typedef operand *(*invocation)(operand **, unsigned long);
typedef unsigned short (*preprocessing)(operand **, unsigned long);

struct excel_function {
    char *name;
    invocation invoke;
    preprocessing preprocess;
};

operand *default_invoke(operand ** input, unsigned long arg_count) { return NULL; }
unsigned short default_preprocess(operand ** input, unsigned long arg_count) { return PP_UNKNOWN_NAME; }
// Add other functions below this comment
static const excel_function excel_function_sentinel = { NULL, default_invoke, default_preprocess };
static excel_function *function_list = NULL;

void feed_function_list() {
    // Please, make sure the functions you add are sorted lexicographically (order in dictionaries).
    // Otherwise the dichotomous search will not work and your functions may not be found!!
    function_list = malloc((FUNCTION_COUNT + 1) * sizeof(excel_function));
    function_list[0] = { "ABS", abs_invoke, abs_preprocess };
    function_list[FUNCTION_COUNT] = excel_function_sentinel;
}

extern excel_function dichotomous_function_search(unsigned int start, unsigned int end, char *function_name);
extern excel_function find_function(char *function_name);

#endif //EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H
