//
// Created by RedNeath on 06/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_function_args(const MunitParameter params[], void *data) {
    char *none = "";
    char *one = "15";
    char *two = "15,2";
    char *three = "15,2,2";
    char *with_function = "15,A(2),2";
    char *with_addition = "15,2+2";
    char *with_priority_operation = "15,(2+2)*2";
    char *incorrect = "A(";
    char *incorrect2 = "A)";

    formula_context context = create_context(1);

    formula_token **tokens_none = parse_function_args(&context, none);
    formula_token **tokens_one = parse_function_args(&context, one);
    formula_token **tokens_two = parse_function_args(&context, two);
    formula_token **tokens_three = parse_function_args(&context, three);
    formula_token **tokens_with_function = parse_function_args(&context, with_function);
    formula_token **tokens_with_addition = parse_function_args(&context, with_addition);
    formula_token **tokens_with_priority_operation = parse_function_args(&context, with_priority_operation);
    formula_token **tokens_incorrect = parse_function_args(&context, incorrect);
    formula_token **tokens_incorrect2 = parse_function_args(&context, incorrect2);

    munit_assert_ushort(TYPE_TOKEN_NONE, ==, tokens_none[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, tokens_one[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, tokens_one[1]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, tokens_two[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, tokens_two[1]->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, tokens_two[2]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, tokens_three[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, tokens_three[1]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, tokens_three[2]->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, tokens_three[3]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, tokens_with_function[0]->type);
    munit_assert_ushort(TYPE_TOKEN_FUNCTION, ==, tokens_with_function[1]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, tokens_with_function[2]->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, tokens_with_function[3]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, tokens_with_addition[0]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, tokens_with_addition[1]->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, tokens_with_addition[2]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, tokens_with_priority_operation[0]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, tokens_with_priority_operation[1]->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, tokens_with_priority_operation[2]->type);
    munit_assert_null(tokens_incorrect);
    munit_assert_null(tokens_incorrect2);

    munit_assert_string_equal("15", tokens_one[0]->value);
    munit_assert_string_equal("15", tokens_two[0]->value);
    munit_assert_string_equal("2", tokens_two[1]->value);
    munit_assert_string_equal("15", tokens_three[0]->value);
    munit_assert_string_equal("2", tokens_three[1]->value);
    munit_assert_string_equal("2", tokens_three[2]->value);
    munit_assert_string_equal("15", tokens_with_function[0]->value);
    munit_assert_string_equal("A", tokens_with_function[1]->value);
    munit_assert_string_equal("2", tokens_with_function[2]->value);
    munit_assert_string_equal("15", tokens_with_addition[0]->value);
    munit_assert_string_equal("+", tokens_with_addition[1]->value);
    munit_assert_string_equal("15", tokens_with_priority_operation[0]->value);
    munit_assert_string_equal("*", tokens_with_priority_operation[1]->value);

    free_token(tokens_none[0]);
    free(tokens_none);
    free_token(tokens_one[0]);
    free_token(tokens_one[1]);
    free(tokens_one);
    free_token(tokens_two[0]);
    free_token(tokens_two[1]);
    free_token(tokens_two[2]);
    free(tokens_two);
    free_token(tokens_three[0]);
    free_token(tokens_three[1]);
    free_token(tokens_three[2]);
    free_token(tokens_three[3]);
    free(tokens_three);
    free_token(tokens_with_function[0]);
    free_token(tokens_with_function[1]);
    free_token(tokens_with_function[2]);
    free_token(tokens_with_function[3]);
    free(tokens_with_function);
    free_token(tokens_with_addition[0]);
    free_token(tokens_with_addition[1]);
    free_token(tokens_with_addition[2]);
    free(tokens_with_addition);
    free_token(tokens_with_priority_operation[0]);
    free_token(tokens_with_priority_operation[1]);
    free_token(tokens_with_priority_operation[2]);
    free(tokens_with_priority_operation);
    free(tokens_incorrect);
    free(tokens_incorrect2);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
