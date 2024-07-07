//
// Created by RedNeath on 05/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_power(const MunitParameter params[], void *data) {
    char *power = "1^15";
    char *wrong = "^15";
    char *wrong1 = "1^";
    char *wrong2 = "^";
    char *wrong3 = "";

    formula_context context = create_context(1);

    formula_token *token_power = parse_power(&context, power);
    formula_token *token_wrong = parse_power(&context, wrong);
    formula_token *token_wrong1 = parse_power(&context, wrong1);
    formula_token *token_wrong2 = parse_power(&context, wrong2);
    formula_token *token_wrong3 = parse_power(&context, wrong3);

    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token_power->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong1->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong2->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong3->type);

    munit_assert_string_equal("^", token_power->value);

    free_token(token_power);
    free_token(token_wrong);
    free_token(token_wrong1);
    free_token(token_wrong2);
    free_token(token_wrong3);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
