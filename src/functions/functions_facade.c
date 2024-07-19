//
// Created by RedNeath on 01/06/24.
//

#include "functions_facade.h"

excel_function **function_list = NULL;

excel_function *excel_function_sentinel() {
    excel_function *sentinel = malloc(sizeof(excel_function));
    sentinel->name = NULL;
    sentinel->invoke = default_invoke;
    sentinel->preprocess = default_preprocess;
    return sentinel;
}

excel_function **get_function_list() {
    if (function_list == NULL) {
        feed_function_list();
    }

    return function_list;
}

void feed_function_list() {
    // Please, make sure the functions you add are sorted lexicographically (order in dictionaries).
    // Otherwise the dichotomous search will not work and your functions may not be found!!
    excel_function *abs_en = malloc(sizeof(excel_function));
    abs_en->name = "ABS"; abs_en->invoke = abs_invoke; abs_en->preprocess = abs_preprocess;

    function_list = malloc((FUNCTION_COUNT + 1) * sizeof(excel_function *));
    function_list[0] = abs_en;
    function_list[FUNCTION_COUNT] = excel_function_sentinel();
}

excel_function *dichotomous_function_search(unsigned int start, unsigned int end, char *function_name) {
    if (start > end) return excel_function_sentinel();
    excel_function **functions = get_function_list();

    unsigned int middle = (start + end) / 2;
    if (functions[middle]->name == NULL) return excel_function_sentinel(); // Sentinel value met
    int comparison = strcmp(functions[middle]->name, function_name);

    if (comparison == 0) return functions[middle];
    if (comparison > 0) return dichotomous_function_search(start, middle - 1, function_name);
    else return dichotomous_function_search(middle + 1, end, function_name);
}

excel_function *find_function(char *function_name) {
    return dichotomous_function_search(0, FUNCTION_COUNT, function_name);
}

operand *default_invoke(operand ** input, unsigned long arg_count) { return NULL; }
unsigned short default_preprocess(operand ** input, unsigned long arg_count) { return PP_UNKNOWN_NAME; }
