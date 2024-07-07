//
// Created by RedNeath on 04/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_function(const MunitParameter params[], void *data) {
    char *function = "PI()";
    char *short_function = "A()";
    char *incorrect = "()";
    char *incorrect2 = "A)";
    char *incorrect3 = "A(";
    char *incorrect4 = "A()A";

    formula_context context = create_context(1);

    formula_token *token_function = parse_function(&context, function);
    formula_token *token_short_function = parse_function(&context, short_function);
    formula_token *token_incorrect = parse_function(&context, incorrect);
    formula_token *token_incorrect2 = parse_function(&context, incorrect2);
    formula_token *token_incorrect3 = parse_function(&context, incorrect3);
    formula_token *token_incorrect4 = parse_function(&context, incorrect4);

    munit_assert_ushort(TYPE_TOKEN_FUNCTION, ==, token_function->type);
    munit_assert_ushort(TYPE_TOKEN_FUNCTION, ==, token_short_function->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_incorrect->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_incorrect2->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_incorrect3->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_incorrect4->type);

    munit_assert_string_equal("PI", token_function->value);
    munit_assert_string_equal("A", token_short_function->value);

    free_token(token_function);
    free_token(token_short_function);
    free_token(token_incorrect);
    free_token(token_incorrect2);
    free_token(token_incorrect3);
    free_token(token_incorrect4);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop

