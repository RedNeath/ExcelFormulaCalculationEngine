//
// Created by RedNeath on 04/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_comparison(const MunitParameter params[], void *data) {
    char *comparison = "12=14";
    char *comparison2 = "12>14";
    char *comparison3 = "12<14";
    char *comparison4 = "12<=14";
    char *comparison5 = "12>=14";
    char *comparison6 = "12<>14";
    char *wrong = "12=";
    char *wrong2 = "12>";
    char *wrong3 = "12<";
    char *wrong4 = "12<=";
    char *wrong5 = "12>=";
    char *wrong6 = "12<>";
    char *wrong7 = "=12";
    char *wrong8 = ">12";
    char *wrong9 = "<12";
    char *wrong10 = "<=12";
    char *wrong11 = ">=12";
    char *wrong12 = "<>12";
    char *incorrect = "12";
    char *incorrect2 = "";

    formula_context context = create_context(1);

    formula_token *token_comparison = parse_comparison(&context, comparison);
    formula_token *token_comparison2 = parse_comparison(&context, comparison2);
    formula_token *token_comparison3 = parse_comparison(&context, comparison3);
    formula_token *token_comparison4 = parse_comparison(&context, comparison4);
    formula_token *token_comparison5 = parse_comparison(&context, comparison5);
    formula_token *token_comparison6 = parse_comparison(&context, comparison6);
    formula_token *token_wrong = parse_comparison(&context, wrong);
    formula_token *token_wrong2 = parse_comparison(&context, wrong2);
    formula_token *token_wrong3 = parse_comparison(&context, wrong3);
    formula_token *token_wrong4 = parse_comparison(&context, wrong4);
    formula_token *token_wrong5 = parse_comparison(&context, wrong5);
    formula_token *token_wrong6 = parse_comparison(&context, wrong6);
    formula_token *token_wrong7 = parse_comparison(&context, wrong7);
    formula_token *token_wrong8 = parse_comparison(&context, wrong8);
    formula_token *token_wrong9 = parse_comparison(&context, wrong9);
    formula_token *token_wrong10 = parse_comparison(&context, wrong10);
    formula_token *token_wrong11 = parse_comparison(&context, wrong11);
    formula_token *token_wrong12 = parse_comparison(&context, wrong12);
    formula_token *token_incorrect = parse_function(&context, incorrect);
    formula_token *token_incorrect2 = parse_function(&context, incorrect2);

    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_comparison->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_comparison2->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_comparison3->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_comparison4->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_comparison5->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_comparison6->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong2->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong3->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong4->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong5->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong6->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong7->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong8->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong9->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong10->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong11->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong12->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_incorrect->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_incorrect2->type);

    munit_assert_string_equal("=", token_comparison->value);
    munit_assert_string_equal(">", token_comparison2->value);
    munit_assert_string_equal("<", token_comparison3->value);
    munit_assert_string_equal("<=", token_comparison4->value);
    munit_assert_string_equal(">=", token_comparison5->value);
    munit_assert_string_equal("<>", token_comparison6->value);

    free_token(token_comparison);
    free_token(token_comparison2);
    free_token(token_comparison3);
    free_token(token_comparison4);
    free_token(token_comparison5);
    free_token(token_comparison6);
    free_token(token_wrong);
    free_token(token_wrong2);
    free_token(token_wrong3);
    free_token(token_wrong4);
    free_token(token_wrong5);
    free_token(token_wrong6);
    free_token(token_wrong7);
    free_token(token_wrong8);
    free_token(token_wrong9);
    free_token(token_wrong10);
    free_token(token_wrong11);
    free_token(token_wrong12);
    free_token(token_incorrect);
    free_token(token_incorrect2);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
