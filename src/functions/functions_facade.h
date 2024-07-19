//
// Created by RedNeath on 31/05/24.
//
#pragma once
#ifndef EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H
#define EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H

#include "../context.h"
#include "../processing/pre_processor.h"

#define FUNCTION_NONE 0
#define FUNCTION_COUNT 1

typedef struct excel_function excel_function;
typedef unsigned short (*preprocessing)(operand **, unsigned long);

/* Import the functions */
#include "mathematics_and_trigonometry/abs.h"

struct excel_function {
    char *name;
    calculation invoke;
    preprocessing preprocess;
};

extern excel_function **function_list __attribute__((unused));

extern excel_function *excel_function_sentinel();
extern excel_function **get_function_list();
extern void feed_function_list();

extern excel_function *dichotomous_function_search(unsigned int start, unsigned int end, char *function_name);
extern excel_function *find_function(char *function_name);

extern operand *default_invoke(operand ** input, unsigned long arg_count);
extern unsigned short default_preprocess(operand ** input, unsigned long arg_count);

#endif //EXCELFORMULACALCULATIONENGINE_FUNCTIONS_FACADE_H
