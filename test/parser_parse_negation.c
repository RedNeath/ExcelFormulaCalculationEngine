//
// Created by RedNeath on 06/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_negation(const MunitParameter params[], void *data) {
    char *negation = "-15";
    char *wrong = "15-";
    char *wrong2 = "-";
    char *wrong3 = "";

    formula_context context = create_context(1);

    formula_token *token_negation = parse_negation(&context, negation);
    formula_token *token_wrong = parse_negation(&context, wrong);
    formula_token *token_wrong2 = parse_negation(&context, wrong2);
    formula_token *token_wrong3 = parse_negation(&context, wrong3);

    munit_assert_ushort(TYPE_TOKEN_UNARY_OPERATOR, ==, token_negation->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong2->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong3->type);

    munit_assert_string_equal("-", token_negation->value);

    free_token(token_negation);
    free_token(token_wrong);
    free_token(token_wrong2);
    free_token(token_wrong3);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
