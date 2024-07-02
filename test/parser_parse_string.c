//
// Created by RedNeath on 02/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_string(const MunitParameter params[], void *data) {
    char *basic = "\"I_am_a_string\"";
    char *spaces = "\"I am a string\"";
    char *escaped = "\"I am a \"\"string\"\"\"";
    char *unescaped = "\"I am a \"\"string\"\"";
    char *incorrect = "\"\"I am a string\"";

    formula_token *token_basic = parse_string(basic);
    formula_token *token_spaces = parse_string(spaces);
    formula_token *token_escaped = parse_string(escaped);
    formula_token *token_unescaped = parse_string(unescaped);
    formula_token *token_incorrect = parse_string(incorrect);

    munit_assert_ushort(TYPE_TOKEN_STRING, ==, token_basic->type);
    munit_assert_ushort(TYPE_TOKEN_STRING, ==, token_spaces->type);
    munit_assert_ushort(TYPE_TOKEN_STRING, ==, token_escaped->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_unescaped->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_incorrect->type);

    munit_assert_string_equal("I_am_a_string", token_basic->value);
    munit_assert_string_equal("I am a string", token_spaces->value);
    munit_assert_string_equal("I am a \"\"string\"\"", token_escaped->value);

    free_token(token_basic);
    free_token(token_spaces);
    free_token(token_escaped);
    free_token(token_unescaped);
    free_token(token_incorrect);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
