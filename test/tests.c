//
// Created by RedNeath on 09/05/2024.
//
#include "../include/munit.h"

// Test functions
#include "context_create_context_test.c"
#include "context_create_context_with_variables_test.c"
#include "context_fast_insert_variable_test.c"
#include "context_fast_insert_variables_test.c"
#include "context_fast_insert_new_number_variable_test.c"
#include "context_fast_insert_new_boolean_variable_test.c"
#include "context_fast_insert_new_string_variable_test.c"
#include "context_fast_insert_new_date_variable_test.c"
#include "context_insert_variable_test.c"
#include "context_insert_variables_test.c"
#include "context_insert_new_number_variable_test.c"
#include "context_insert_new_boolean_variable_test.c"
#include "context_insert_new_string_variable_test.c"
#include "context_insert_new_date_variable_test.c"
#include "context_get_variable_test.c"
#include "context_set_capacity_test.c"
#include "context_overwrite_variable_test.c"
#include "context_free_context_test.c"
#include "parser_parse_number.c"
#include "parser_parse_boolean.c"
#include "parser_parse_string.c"
#include "parser_parse_value.c"
#include "parser_parse_variable.c"
#include "parser_parse_function.c"
#include "parser_parse_comparison.c"
#include "parser_parse_concatenation.c"
#include "parser_parse_addition_or_subtraction.c"
#include "parser_parse_multiplication_or_division.c"
#include "parser_parse_power.c"
#include "parser_parse_percent.c"
#include "parser_parse_negation.c"
#include "parser_parse_parenthesis.c"
#include "parser_parse_expression.c"
#include "parser_parse_function_args.c"
#include "parser_parse_formula.c"

// Defining the list of tests to execute:
static MunitTest test_array[] = {
    { "/context/create_context                 \t\t", test_create_context, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/create_context_with_variables  \t\t", test_create_context_with_variables, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_variable           \t\t", test_fast_insert_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_variables          \t\t", test_fast_insert_variables, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_new_number_variable\t\t", test_fast_insert_new_number_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_new_rate_variable  \t\t", test_fast_insert_new_boolean_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_new_string_variable\t\t", test_fast_insert_new_string_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_new_date_variable  \t\t", test_fast_insert_new_date_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_variable                \t\t", test_insert_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_variables               \t\t", test_insert_variables, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_number_variable     \t\t", test_insert_new_number_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_rate_variable       \t\t", test_insert_new_boolean_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_string_variable     \t\t", test_insert_new_string_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_date_variable       \t\t", test_insert_new_date_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/get_variable                   \t\t", test_get_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/set_capacity                   \t\t", test_set_capacity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/overwrite_variable             \t\t", test_overwrite_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/free_context                   \t\t", test_free_context, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_number                    \t\t", test_parse_number, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_boolean                   \t\t", test_parse_boolean, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_string                    \t\t", test_parse_string, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_value                     \t\t", test_parse_value, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_variable                  \t\t", test_parse_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_function                  \t\t", test_parse_function, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_comparison                \t\t", test_parse_comparison, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_concatenation             \t\t", test_parse_concatenation, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_addition_or_subtraction   \t\t", test_parse_addition_or_subtraction, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_multiplication_or_division\t\t", test_parse_multiplication_or_division, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_power                     \t\t", test_parse_power, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_percent                   \t\t", test_parse_percent, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_negation                  \t\t", test_parse_negation, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_parenthesis               \t\t", test_parse_parenthesis, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_expression                \t\t", test_parse_expression, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_function_args             \t\t", test_parse_function_args, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_formula                   \t\t", test_parse_formula, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    // Last item must be this one (it is used to identify that this is the end of the list).
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

// Defining the test suite:
static const MunitSuite test_suite = {
    (char *) "",
    test_array,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, "server", argc, argv);
}
