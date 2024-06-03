//
// Created by redneath on 01/06/24.
//

#include "functions_facade.h"

excel_function dichotomous_function_search(unsigned int start, unsigned int end, char *function_name) {
    if (start > end) return excel_function_sentinel;

    unsigned int middle = (start + end) / 2;
    if (function_list[middle].name == NULL) return excel_function_sentinel; // Sentinel value met
    int comparison = strcmp(function_list[middle].name, function_name);

    if (comparison == 0) return function_list[middle];
    if (comparison > 0) return dichotomous_function_search(start, middle - 1, function_name);
    else return dichotomous_function_search(middle + 1, end, function_name);
}

unsigned int find_function(char *function_name) {
    unsigned int max = FUNCTION_COUNT;

    excel_function matching = dichotomous_function_search(0, max, function_name);
    return matching.index;
}

formula_variable *invoke(char *function_name, formula_variable *args) {
    unsigned int index = find_function(function_name);

    switch(index) {
        // Add function case below

        case FUNCTION_NONE:
        default:
            return &formula_variable_sentinel;
    }
}
