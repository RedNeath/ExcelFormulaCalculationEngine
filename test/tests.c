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
#include "pre_processor_preprocess_test.c"
// #include "pre_processor_resolve_operands_test.c"
// #include "pre_processor_resolve_boolean_operand_test.c"
// #include "pre_processor_resolve_number_operand_test.c"
// #include "pre_processor_resolve_string_operand_test.c"
// #include "pre_processor_resolve_variable_operand_test.c"
// #include "pre_processor_preprocess_unary_operator_test.c"
// #include "pre_processor_preprocess_negation_test.c"
// #include "pre_processor_preprocess_percent_test.c"
// #include "pre_processor_preprocess_binary_operator_test.c"
// #include "pre_processor_preprocess_number_operator_test.c"
// #include "pre_processor_preprocess_power_test.c"
// #include "pre_processor_preprocess_multiplication_test.c"
// #include "pre_processor_preprocess_division_test.c"
// #include "pre_processor_preprocess_addition_test.c"
// #include "pre_processor_preprocess_subtraction_test.c"
// #include "pre_processor_preprocess_concatenation_test.c"
// #include "pre_processor_preprocess_equality_test.c"
// #include "pre_processor_preprocess_strict_superiority_test.c"
// #include "pre_processor_preprocess_strict_inferiority_test.c"
// #include "pre_processor_preprocess_superiority_test.c"
// #include "pre_processor_preprocess_inferiority_test.c"
// #include "pre_processor_preprocess_difference_test.c"
// #include "pre_processor_preprocess_function_test.c"
// #include "pre_processor_try_number_cast_test.c"
// #include "pre_processor_try_string_cast_test.c"
// #include "pre_processor_get_child_count_test.c"
// #include "pre_processor_get_operand_count_test.c"

// Defining the list of tests to execute:
static MunitTest test_array[] = {
    { "/context/create_context                     \t\t", test_create_context, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/create_context_with_variables      \t\t", test_create_context_with_variables, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_variable               \t\t", test_fast_insert_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_variables              \t\t", test_fast_insert_variables, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_new_number_variable    \t\t", test_fast_insert_new_number_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_new_rate_variable      \t\t", test_fast_insert_new_boolean_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_new_string_variable    \t\t", test_fast_insert_new_string_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/fast_insert_new_date_variable      \t\t", test_fast_insert_new_date_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_variable                    \t\t", test_insert_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_variables                   \t\t", test_insert_variables, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_number_variable         \t\t", test_insert_new_number_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_rate_variable           \t\t", test_insert_new_boolean_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_string_variable         \t\t", test_insert_new_string_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_date_variable           \t\t", test_insert_new_date_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/get_variable                       \t\t", test_get_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/set_capacity                       \t\t", test_set_capacity, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/overwrite_variable                 \t\t", test_overwrite_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/free_context                       \t\t", test_free_context, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_number                        \t\t", test_parse_number, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_boolean                       \t\t", test_parse_boolean, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_string                        \t\t", test_parse_string, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_value                         \t\t", test_parse_value, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_variable                      \t\t", test_parse_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_function                      \t\t", test_parse_function, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_comparison                    \t\t", test_parse_comparison, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_concatenation                 \t\t", test_parse_concatenation, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_addition_or_subtraction       \t\t", test_parse_addition_or_subtraction, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_multiplication_or_division    \t\t", test_parse_multiplication_or_division, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_power                         \t\t", test_parse_power, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_percent                       \t\t", test_parse_percent, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_negation                      \t\t", test_parse_negation, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_parenthesis                   \t\t", test_parse_parenthesis, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_expression                    \t\t", test_parse_expression, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_function_args                 \t\t", test_parse_function_args, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/parser/parse_formula                       \t\t", test_parse_formula, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/pre_processor/preprocess                   \t\t", test_preprocess, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/resolve_operands             \t\t", test_resolve_operands, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/resolve_boolean_operand      \t\t", test_resolve_boolean_operand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/resolve_number_operand       \t\t", test_resolve_number_operand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/resolve_string_operand       \t\t", test_resolve_string_operand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/resolve_variable_operand     \t\t", test_resolve_variable_operand, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_unary_operator    \t\t", test_preprocess_unary_operator, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_negation          \t\t", test_preprocess_negation, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_percent           \t\t", test_preprocess_percent, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_binary_operator   \t\t", test_preprocess_binary_operator, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_number_operator   \t\t", test_preprocess_number_operator, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_power             \t\t", test_preprocess_power, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_multiplication    \t\t", test_preprocess_multiplication, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_division          \t\t", test_preprocess_division, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_addition          \t\t", test_preprocess_addition, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_subtraction       \t\t", test_preprocess_subtraction, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_concatenation     \t\t", test_preprocess_concatenation, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_equality          \t\t", test_preprocess_equality, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_strict_superiority\t\t", test_preprocess_strict_superiority, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_strict_inferiority\t\t", test_preprocess_strict_inferiority, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_superiority       \t\t", test_preprocess_superiority, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_inferiority       \t\t", test_preprocess_inferiority, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_difference        \t\t", test_preprocess_difference, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/preprocess_function          \t\t", test_preprocess_function, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/try_number_cast              \t\t", test_try_number_cast, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/try_string_cast              \t\t", test_try_string_cast, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/get_child_count              \t\t", test_get_child_count, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    // { "/pre_processor/get_operand_count            \t\t", test_get_operand_count, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

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
