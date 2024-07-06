//
// Created by RedNeath on 05/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_addition_or_subtraction(const MunitParameter params[], void *data) {
    char *addition = "1+15";
    char *subtraction = "1-15";
    char *wrong = "+15";
    char *wrong2 = "1+";
    char *wrong3 = "-15";
    char *wrong4 = "1-";
    char *wrong5 = "+";
    char *wrong6 = "-";
    char *wrong7 = "";

    formula_context context = create_context(1);

    formula_token *token_addition = parse_addition_or_subtraction(&context, addition);
    formula_token *token_subtraction = parse_addition_or_subtraction(&context, subtraction);
    formula_token *token_wrong = parse_addition_or_subtraction(&context, wrong);
    formula_token *token_wrong2 = parse_addition_or_subtraction(&context, wrong2);
    formula_token *token_wrong3 = parse_addition_or_subtraction(&context, wrong3);
    formula_token *token_wrong4 = parse_addition_or_subtraction(&context, wrong4);
    formula_token *token_wrong5 = parse_addition_or_subtraction(&context, wrong5);
    formula_token *token_wrong6 = parse_addition_or_subtraction(&context, wrong6);
    formula_token *token_wrong7 = parse_addition_or_subtraction(&context, wrong7);

    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_addition->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_subtraction->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong2->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong3->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong4->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong5->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong6->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong7->type);

    munit_assert_string_equal("+", token_addition->value);
    munit_assert_string_equal("-", token_subtraction->value);

    free_token(token_addition);
    free_token(token_subtraction);
    free_token(token_wrong);
    free_token(token_wrong2);
    free_token(token_wrong3);
    free_token(token_wrong4);
    free_token(token_wrong5);
    free_token(token_wrong6);
    free_token(token_wrong7);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
