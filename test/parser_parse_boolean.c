//
// Created by RedNeath on 02/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_boolean(const MunitParameter params[], void *data) {
    char *true_string = "TRUE";
    char *false_string = "FALSE";
    char *fake_true_string = "true";
    char *fake_false_string = "false";
    char *random_string = "ljenz";

    formula_token *token_true = parse_boolean(true_string);
    formula_token *token_false = parse_boolean(false_string);
    formula_token *token_fake_true = parse_boolean(fake_true_string);
    formula_token *token_fake_false = parse_boolean(fake_false_string);
    formula_token *token_random = parse_boolean(random_string);

    munit_assert_ushort(TYPE_TOKEN_BOOLEAN, ==, token_true->type);
    munit_assert_ushort(TYPE_TOKEN_BOOLEAN, ==, token_false->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_fake_true->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_fake_false->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_random->type);

    munit_assert_string_equal("TRUE", token_true->value);
    munit_assert_string_equal("FALSE", token_false->value);

    free_token(token_true);
    free_token(token_false);
    free_token(token_fake_true);
    free_token(token_fake_false);
    free_token(token_random);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
