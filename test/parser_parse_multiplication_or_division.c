//
// Created by RedNeath on 05/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_multiplication_or_division(const MunitParameter params[], void *data) {
    char *multiplication = "1*15";
    char *division = "1/15";
    char *wrong = "*15";
    char *wrong2 = "1*";
    char *wrong3 = "/15";
    char *wrong4 = "1/";
    char *wrong5 = "*";
    char *wrong6 = "/";
    char *wrong7 = "";

    formula_context context = create_context(1);

    formula_token *token_multiplication = parse_multiplication_or_division(&context, multiplication);
    formula_token *token_division = parse_multiplication_or_division(&context, division);
    formula_token *token_wrong = parse_multiplication_or_division(&context, wrong);
    formula_token *token_wrong2 = parse_multiplication_or_division(&context, wrong2);
    formula_token *token_wrong3 = parse_multiplication_or_division(&context, wrong3);
    formula_token *token_wrong4 = parse_multiplication_or_division(&context, wrong4);
    formula_token *token_wrong5 = parse_multiplication_or_division(&context, wrong5);
    formula_token *token_wrong6 = parse_multiplication_or_division(&context, wrong6);
    formula_token *token_wrong7 = parse_multiplication_or_division(&context, wrong7);

    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_multiplication->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_division->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong2->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong3->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong4->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong5->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong6->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong7->type);

    munit_assert_string_equal("*", token_multiplication->value);
    munit_assert_string_equal("/", token_division->value);

    free_token(token_multiplication);
    free_token(token_division);
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
