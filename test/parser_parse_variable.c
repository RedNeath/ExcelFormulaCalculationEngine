//
// Created by RedNeath on 03/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_variable(const MunitParameter params[], void *data) {
    formula_context context = create_context(1);
    insert_new_number_variable(&context, "A1", 10.75);

    formula_token *token_existing_variable = parse_variable(&context, "A1");
    formula_token *token_non_existing_variable = parse_variable(&context, "afeaz");

    munit_assert_ushort(TYPE_TOKEN_VARIABLE, ==, token_existing_variable->type);
    munit_assert_ushort(TYPE_TOKEN_NONE, ==, token_non_existing_variable->type);

    munit_assert_string_equal("A1", token_existing_variable->value);

    free_token(token_existing_variable);
    free_token(token_non_existing_variable);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
