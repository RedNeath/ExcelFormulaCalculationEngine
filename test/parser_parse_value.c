//
// Created by RedNeath on 03/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_value(const MunitParameter params[], void *data) {
    char *bool_true = "TRUE";
    char *bool_false = "FALSE";
    char *num_int = "15";
    char *num_float = "14.54";
    char *str_basic = "\"I_am_a_string\"";
    char *str_spaces = "\"I am a string\"";
    char *str_escaped = "\"I am a \"\"string\"\"\"";
    char *str_empty = "\"\"";
    char *incorrect = "pkpnf4ze4";

    formula_token *token_bool_true = parse_value(bool_true);
    formula_token *token_bool_false = parse_value(bool_false);
    formula_token *token_num_int = parse_value(num_int);
    formula_token *token_num_float = parse_value(num_float);
    formula_token *token_str_basic = parse_string(str_basic);
    formula_token *token_str_spaces = parse_string(str_spaces);
    formula_token *token_str_escaped = parse_string(str_escaped);
    formula_token *token_str_empty = parse_string(str_empty);
    formula_token *token_incorrect = parse_string(incorrect);

    munit_assert_ushort(TYPE_TOKEN_BOOLEAN, ==, token_bool_true->type);
    munit_assert_ushort(TYPE_TOKEN_BOOLEAN, ==, token_bool_false->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_num_int->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token_num_float->type);
    munit_assert_ushort(TYPE_TOKEN_STRING, ==, token_str_basic->type);
    munit_assert_ushort(TYPE_TOKEN_STRING, ==, token_str_spaces->type);
    munit_assert_ushort(TYPE_TOKEN_STRING, ==, token_str_escaped->type);
    munit_assert_ushort(TYPE_TOKEN_STRING, ==, token_str_empty->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_incorrect->type);

    munit_assert_string_equal("TRUE", token_bool_true->value);
    munit_assert_string_equal("FALSE", token_bool_false->value);
    munit_assert_string_equal("15", token_num_int->value);
    munit_assert_string_equal("14.54", token_num_float->value);
    munit_assert_string_equal("I_am_a_string", token_str_basic->value);
    munit_assert_string_equal("I am a string", token_str_spaces->value);
    munit_assert_string_equal("I am a \"\"string\"\"", token_str_escaped->value);
    munit_assert_string_equal("", token_str_empty->value);

    free_token(token_bool_true);
    free_token(token_bool_false);
    free_token(token_num_int);
    free_token(token_num_float);
    free_token(token_str_basic);
    free_token(token_str_spaces);
    free_token(token_str_escaped);
    free_token(token_str_empty);
    free_token(token_incorrect);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
