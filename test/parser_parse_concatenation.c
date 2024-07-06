//
// Created by RedNeath on 05/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_concatenation(const MunitParameter params[], void *data) {
    char *concatenation = "\"A\"&\"B\"";
    char *wrong = "&\"B\"";
    char *wrong2 = "\"A\"&";
    char *wrong3 = "&";
    char *wrong4 = "";

    formula_context context = create_context(1);

    formula_token *token_concatenation = parse_concatenation(&context, concatenation);
    formula_token *token_wrong = parse_concatenation(&context, wrong);
    formula_token *token_wrong2 = parse_concatenation(&context, wrong2);
    formula_token *token_wrong3 = parse_concatenation(&context, wrong3);
    formula_token *token_wrong4 = parse_concatenation(&context, wrong4);

    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_concatenation->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong2->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong3->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong4->type);

    munit_assert_string_equal("&", token_concatenation->value);

    free_token(token_concatenation);
    free_token(token_wrong);
    free_token(token_wrong2);
    free_token(token_wrong3);
    free_token(token_wrong4);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
