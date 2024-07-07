//
// Created by RedNeath on 01/07/2024.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_number(const MunitParameter params[], void *data) {
    char *integer_number = "1";
    char *floating_number = "1.02";
    char *not_a_number = "not a number";
    char *starting_with_number = "120bjrar";
    char *ending_with_number = "earfa19";

    formula_token *token_integer_number = parse_number(integer_number);
    formula_token *token_floating_number = parse_number(floating_number);
    formula_token *token_not_a_number = parse_number(not_a_number);
    formula_token *token_starting_with_number = parse_number(starting_with_number);
    formula_token *token_ending_with_number = parse_number(ending_with_number);

    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_integer_number->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_floating_number->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_not_a_number->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_starting_with_number->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_ending_with_number->type);

    munit_assert_string_equal("1", token_integer_number->value);
    munit_assert_string_equal("1.02", token_floating_number->value);

    free_token(token_integer_number);
    free_token(token_floating_number);
    free_token(token_not_a_number);
    free_token(token_starting_with_number);
    free_token(token_ending_with_number);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
