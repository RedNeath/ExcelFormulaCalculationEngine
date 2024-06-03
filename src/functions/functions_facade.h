//
// Created by redneath on 31/05/24.
//

#ifndef EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H
#define EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H

#include "../context.h"

#define FUNCTION_NONE 0
#define FUNCTION_COUNT 0

/* Import the functions */
//#include "???.h"

typedef struct excel_function excel_function;

struct excel_function {
    char *name;
    unsigned int index;
};

// Add other functions below this comment
static const excel_function excel_function_sentinel = { NULL, 0 };
static excel_function *function_list = NULL;

void feed_function_list() {
    // Please, make sure the functions you add are sorted lexicographically (order in dictionnaries).
    // Otherwise the dichotomous search will not work and your functions may not be found!!
    function_list = malloc((FUNCTION_COUNT + 1) * sizeof(excel_function));
    function_list[0] = excel_function_sentinel;
}

extern excel_function dichotomous_function_search(unsigned int start, unsigned int end, char *function_name);
extern unsigned int find_function(char *function_name);

extern formula_variable *invoke(char *function_name, formula_variable *args);

#endif //EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H
