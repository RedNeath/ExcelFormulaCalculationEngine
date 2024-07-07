//
// Created by RedNeath on 06/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_parenthesis(const MunitParameter params[], void *data) {
    char *parenthesis = "(15)";
    char *wrong = "()";
    char *wrong2 = "(";
    char *wrong3 = ")";
    char *wrong4 = "";

    formula_context context = create_context(1);

    formula_token *token_parenthesis = parse_parenthesis(&context, parenthesis);
    formula_token *token_wrong = parse_parenthesis(&context, wrong);
    formula_token *token_wrong2 = parse_parenthesis(&context, wrong2);
    formula_token *token_wrong3 = parse_parenthesis(&context, wrong3);
    formula_token *token_wrong4 = parse_parenthesis(&context, wrong4);

    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_parenthesis->type);
    munit_assert_null(token_wrong); // empty expression
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong2->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong3->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_wrong4->type);

    free_token(token_parenthesis);
    free_token(token_wrong);
    free_token(token_wrong2);
    free_token(token_wrong3);
    free_token(token_wrong4);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
