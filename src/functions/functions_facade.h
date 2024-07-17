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
typedef operand *(*invocation)(operand *);
typedef unsigned short (*preprocessing)(operand *);

struct excel_function {
    char *name;
    invocation invoke;
    preprocessing preprocess;
};

operand *def_invoke(operand *) { return NULL; }
unsigned short def_preprocess(operand *) { return PP_INCORRECT_VALUE; }
// Add other functions below this comment
static const excel_function excel_function_sentinel = { NULL, def_invoke, def_preprocess };
static excel_function *function_list = NULL;

void feed_function_list() {
    // Please, make sure the functions you add are sorted lexicographically (order in dictionaries).
    // Otherwise the dichotomous search will not work and your functions may not be found!!
    function_list = malloc((FUNCTION_COUNT + 1) * sizeof(excel_function));
    function_list[0] = { "ABS", abs_invoke, abs_preprocess };
    function_list[FUNCTION_COUNT] = excel_function_sentinel;
}

extern excel_function dichotomous_function_search(unsigned int start, unsigned int end, char *function_name);
extern unsigned int find_function(char *function_name);

#endif //EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H
