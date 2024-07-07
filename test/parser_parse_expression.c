//
// Created by RedNeath on 06/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_expression(const MunitParameter params[], void *data) {
    // We need test for:
    //  - different operators and result token types
    //  - priority between operations
    //  - few error cases
    char *comparison = "15=2";
    char *concatenation = "\"A\"&\"B\"";
    char *addition = "15+2";
    char *subtraction = "15-2";
    char *multiplication = "15*2";
    char *division = "15/2";
    char *power = "15^2";
    char *percent = "15%";
    char *negation = "-15";
    char *parenthesis = "(15)";
    char *function = "A()";
    char *value = "15";
    char *variable = "A1";

    char *priority1 = "15=2+2";
    char *priority2 = "(15=2)+2";

    char *wrong = "()";
    char *wrong2 = "";

    formula_context context = create_context(1);
    insert_new_number_variable(&context, "A1", 10.75);

    formula_token *token_comparison = parse_expression(&context, comparison);
    formula_token *token_concatenation = parse_expression(&context, concatenation);
    formula_token *token_addition = parse_expression(&context, addition);
    formula_token *token_subtraction = parse_expression(&context, subtraction);
    formula_token *token_multiplication = parse_expression(&context, multiplication);
    formula_token *token_division = parse_expression(&context, division);
    formula_token *token_power = parse_expression(&context, power);
    formula_token *token_percent = parse_expression(&context, percent);
    formula_token *token_negation = parse_expression(&context, negation);
    formula_token *token_parenthesis = parse_expression(&context, parenthesis);
    formula_token *token_function = parse_expression(&context, function);
    formula_token *token_value = parse_expression(&context, value);
    formula_token *token_variable = parse_expression(&context, variable);
    formula_token *token_priority1 = parse_expression(&context, priority1);
    formula_token *token_priority2 = parse_expression(&context, priority2);
    formula_token *token_wrong = parse_expression(&context, wrong);
    formula_token *token_wrong2 = parse_expression(&context, wrong2);



    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_comparison->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_comparison->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_comparison->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_concatenation->type);
    munit_assert_ushort(TYPE_TOKEN_STRING, ==, token_concatenation->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_STRING, ==, token_concatenation->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_addition->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_addition->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_addition->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_subtraction->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_subtraction->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_subtraction->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_multiplication->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_multiplication->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_multiplication->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_division->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_division->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_division->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_power->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_power->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_power->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_UNARY_OPERATOR, ==, token_percent->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_percent->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_UNARY_OPERATOR, ==, token_negation->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_negation->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_parenthesis->type);
    munit_assert_ushort(TYPE_TOKEN_FUNCTION, ==, token_function->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_function->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_value->type);
    munit_assert_ushort(TYPE_TOKEN_VARIABLE, ==, token_variable->type);
    // Priority
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_priority1->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_priority1->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_priority1->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_priority1->children[1]->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_priority1->children[1]->children[1]->type);
    // Priority 2
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_priority2->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_priority2->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_priority2->children[0]->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_priority2->children[0]->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_priority2->children[1]->type);
    // "Error" cases
    munit_assert_null(token_wrong);
    munit_assert_null(token_wrong2);



    munit_assert_string_equal("=", token_comparison->value);
    munit_assert_string_equal("15", token_comparison->children[0]->value);
    munit_assert_string_equal("2", token_comparison->children[1]->value);
    munit_assert_string_equal("&", token_concatenation->value);
    munit_assert_string_equal("A", token_concatenation->children[0]->value);
    munit_assert_string_equal("B", token_concatenation->children[1]->value);
    munit_assert_string_equal("+", token_addition->value);
    munit_assert_string_equal("15", token_addition->children[0]->value);
    munit_assert_string_equal("2", token_addition->children[1]->value);
    munit_assert_string_equal("-", token_subtraction->value);
    munit_assert_string_equal("15", token_subtraction->children[0]->value);
    munit_assert_string_equal("2", token_subtraction->children[1]->value);
    munit_assert_string_equal("*", token_multiplication->value);
    munit_assert_string_equal("15", token_multiplication->children[0]->value);
    munit_assert_string_equal("2", token_multiplication->children[1]->value);
    munit_assert_string_equal("/", token_division->value);
    munit_assert_string_equal("15", token_division->children[0]->value);
    munit_assert_string_equal("2", token_division->children[1]->value);
    munit_assert_string_equal("^", token_power->value);
    munit_assert_string_equal("15", token_power->children[0]->value);
    munit_assert_string_equal("2", token_power->children[1]->value);
    munit_assert_string_equal("%", token_percent->value);
    munit_assert_string_equal("15", token_percent->children[0]->value);
    munit_assert_string_equal("-", token_negation->value);
    munit_assert_string_equal("15", token_negation->children[0]->value);
    munit_assert_string_equal("15", token_parenthesis->value);
    munit_assert_string_equal("A", token_function->value);
    munit_assert_string_equal("15", token_value->value);
    munit_assert_string_equal("A1", token_variable->value);
    // Priority
    munit_assert_string_equal("=", token_priority1->value);
    munit_assert_string_equal("15", token_priority1->children[0]->value);
    munit_assert_string_equal("+", token_priority1->children[1]->value);
    munit_assert_string_equal("2", token_priority1->children[1]->children[0]->value);
    munit_assert_string_equal("2", token_priority1->children[1]->children[1]->value);
    // Priority 2
    munit_assert_string_equal("+", token_priority2->value);
    munit_assert_string_equal("=", token_priority2->children[0]->value);
    munit_assert_string_equal("15", token_priority2->children[0]->children[0]->value);
    munit_assert_string_equal("2", token_priority2->children[0]->children[1]->value);
    munit_assert_string_equal("2", token_priority2->children[1]->value);

    free_token(token_comparison);
    free_token(token_concatenation);
    free_token(token_addition);
    free_token(token_subtraction);
    free_token(token_multiplication);
    free_token(token_division);
    free_token(token_power);
    free_token(token_percent);
    free_token(token_negation);
    free_token(token_parenthesis);
    free_token(token_function);
    free_token(token_value);
    free_token(token_variable);
    free_token(token_priority1);
    free_token(token_priority2);
    free_token(token_wrong);
    free_token(token_wrong2);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
