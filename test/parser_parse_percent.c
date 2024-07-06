//
// Created by RedNeath on 05/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_percent(const MunitParameter params[], void *data) {
    char *percent = "15%";
    char *wrong = "%15";
    char *wrong2 = "%";
    char *wrong3 = "";

    formula_context context = create_context(1);

    formula_token *token_percent = parse_percent(&context, percent);
    formula_token *token_wrong = parse_percent(&context, wrong);
    formula_token *token_wrong2 = parse_percent(&context, wrong2);
    formula_token *token_wrong3 = parse_percent(&context, wrong3);

    munit_assert_ushort(TYPE_TOKEN_UNARY_OPERATOR, ==, token_percent->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong2->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong3->type);

    munit_assert_string_equal("%", token_percent->value);

    free_token(token_percent);
    free_token(token_wrong);
    free_token(token_wrong2);
    free_token(token_wrong3);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
