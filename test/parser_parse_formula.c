//
// Created by RedNeath on 07/07/24.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_formula(const MunitParameter params[], void *data) {
    // =IF(A1>A2,AVG(B1,B2,B3,B4,B5),187)*COEFF/(12+7*3)
    char *formula = "=IF(A1>A2,AVG(B1,B2,B3,B4,B5),187)*COEFF/(12+7*3)";

    char *wrong = "";
    char *wrong2 = "=";

    formula_context context = create_context(8);
    insert_new_number_variable(&context, "A1", 12);
    insert_new_number_variable(&context, "A2", 45);
    insert_new_number_variable(&context, "B1", 13);
    insert_new_number_variable(&context, "B2", 5);
    insert_new_number_variable(&context, "B3", 74);
    insert_new_number_variable(&context, "B4", 6);
    insert_new_number_variable(&context, "B5", 41);
    insert_new_number_variable(&context, "COEFF", 0.58);

    formula_token *token = parse_formula(&context, formula);
    formula_token *token_wrong = parse_formula(&context, wrong);
    formula_token *token_wrong2 = parse_formula(&context, wrong2);

    // See the tree in the example diagram from the documentation
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_FUNCTION, ==, token->children[0]->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token->children[0]->children[0]->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_VARIABLE, ==, token->children[0]->children[0]->children[0]->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_VARIABLE, ==, token->children[0]->children[0]->children[0]->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_FUNCTION, ==, token->children[0]->children[0]->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_VARIABLE, ==, token->children[0]->children[0]->children[1]->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_VARIABLE, ==, token->children[0]->children[0]->children[1]->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_VARIABLE, ==, token->children[0]->children[0]->children[1]->children[2]->type);
    munit_assert_ushort(TYPE_TOKEN_VARIABLE, ==, token->children[0]->children[0]->children[1]->children[3]->type);
    munit_assert_ushort(TYPE_TOKEN_VARIABLE, ==, token->children[0]->children[0]->children[1]->children[4]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token->children[0]->children[0]->children[2]->type);
    munit_assert_ushort(TYPE_TOKEN_VARIABLE, ==, token->children[0]->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token->children[1]->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_BINARY_OPERATOR, ==, token->children[1]->children[1]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token->children[1]->children[1]->children[0]->type);
    munit_assert_ushort(TYPE_TOKEN_NUMBER, ==, token->children[1]->children[1]->children[1]->type);

    munit_assert_null(token_wrong);
    munit_assert_null(token_wrong2);

    munit_assert_string_equal("/", token->value);
    munit_assert_string_equal("*", token->children[0]->value);
    munit_assert_string_equal("IF", token->children[0]->children[0]->value);
    munit_assert_string_equal(">", token->children[0]->children[0]->children[0]->value);
    munit_assert_string_equal("A1", token->children[0]->children[0]->children[0]->children[0]->value);
    munit_assert_string_equal("A2", token->children[0]->children[0]->children[0]->children[1]->value);
    munit_assert_string_equal("AVG", token->children[0]->children[0]->children[1]->value);
    munit_assert_string_equal("B1", token->children[0]->children[0]->children[1]->children[0]->value);
    munit_assert_string_equal("B2", token->children[0]->children[0]->children[1]->children[1]->value);
    munit_assert_string_equal("B3", token->children[0]->children[0]->children[1]->children[2]->value);
    munit_assert_string_equal("B4", token->children[0]->children[0]->children[1]->children[3]->value);
    munit_assert_string_equal("B5", token->children[0]->children[0]->children[1]->children[4]->value);
    munit_assert_string_equal("187", token->children[0]->children[0]->children[2]->value);
    munit_assert_string_equal("COEFF", token->children[0]->children[1]->value);
    munit_assert_string_equal("+", token->children[1]->value);
    munit_assert_string_equal("12", token->children[1]->children[0]->value);
    munit_assert_string_equal("*", token->children[1]->children[1]->value);
    munit_assert_string_equal("7", token->children[1]->children[1]->children[0]->value);
    munit_assert_string_equal("3", token->children[1]->children[1]->children[1]->value);

    free_token(token);
    free_token(token_wrong);
    free_token(token_wrong2);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
