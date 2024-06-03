//
// Created by redneath on 31/05/24.
//

#ifndef EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H
#define EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H

#include "../context.h"

#define FUNCTION_NONE 0
#define MAX_FUNCTION_INDEX 0

/* Import the functions */
//#include "???.h"

unsigned int find_function(char *function_name);

formula_variable *invoke(char *function_name, formula_variable *args);

#endif //EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H
