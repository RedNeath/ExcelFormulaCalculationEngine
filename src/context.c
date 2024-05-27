//
// Created by Xiaomi on 23/05/2024.
//

#include "context.h"

formula_context create_context(unsigned long initial_capacity) {
    // Allocating the memory
    formula_context context = malloc(initial_capacity+1 * sizeof(formula_variable));
    context.variables[0] = { NULL, NULL, NULL, NULL, TYPE_SENTINEL };

    return context;
}
