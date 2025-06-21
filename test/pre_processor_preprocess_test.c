//
// Created by RedNeath on 15/06/25.
//
#include "../src/processing/pre_processor.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
static MunitResult test_preprocess(const MunitParameter params[], void* user_data) {
    // If we are preprocessing a leaf, unless the leaf is a function, we'll always get
    // a NULL returned;
    // In other cases, we're supposed to get an `operation` with the right status,
    // calculation function, and operands.
    //
    // NOTE: order in the operands is important! (always has been) 🥸
    formula_context context = create_context(8);
    insert_new_number_variable(&context, "A1", 12);

    formula_token *boolean_leaf_token = malloc(sizeof(formula_token));
    formula_token *number_leaf_token = malloc(sizeof(formula_token));
    formula_token *string_leaf_token = malloc(sizeof(formula_token));
    formula_token *variable_leaf_token = malloc(sizeof(formula_token));
    formula_token *function_leaf_token = malloc(sizeof(formula_token));

    formula_token *function_branch_token = malloc(sizeof(formula_token));
    formula_token *binary_op_branch_token = malloc(sizeof(formula_token));
    formula_token *unary_op_branch_token = malloc(sizeof(formula_token));


    // Let's create and try those tokens one by one:
    // 1. Boolean leaf token
    boolean_leaf_token->value = "TRUE"; // Should be okay 'cause we're not getting it out of this function
    boolean_leaf_token->type = TYPE_TOKEN_BOOLEAN;
    boolean_leaf_token->children = NULL;

    operation *boolean_leaf_operation = preprocess(&context, boolean_leaf_token);
    munit_assert_null(boolean_leaf_operation);

    // 2. Number leaf token
    number_leaf_token->value = "1"; // Same here
    number_leaf_token->type = TYPE_TOKEN_NUMBER;
    number_leaf_token->children = NULL;

    operation *number_leaf_operation = preprocess(&context, number_leaf_token);
    munit_assert_null(number_leaf_operation);

    // 3. String leaf token
    string_leaf_token->value = "I am a string"; // Same again ^^
    string_leaf_token->type = TYPE_TOKEN_STRING;
    string_leaf_token->children = NULL;

    operation *string_leaf_operation = preprocess(&context, string_leaf_token);
    munit_assert_null(string_leaf_operation);

    // 4. Variable leaf token
    variable_leaf_token->value = "A1";
    variable_leaf_token->type = TYPE_TOKEN_VARIABLE;
    variable_leaf_token->children = NULL;

    operation *variable_leaf_operation = preprocess(&context, variable_leaf_token);
    munit_assert_null(variable_leaf_operation);

    // 5. Function leaf token
    function_leaf_token->value = "PI";
    function_leaf_token->type = TYPE_TOKEN_FUNCTION;
    function_leaf_token->children = NULL;

    operation *function_leaf_operation = preprocess(&context, function_leaf_token);
    munit_assert_not_null(function_leaf_operation);
    munit_assert_ushort(PP_OK, ==, function_leaf_operation->status);
    munit_assert_ushort(TYPE_SENTINEL, ==, function_leaf_operation->operands[0]->type); // Implicitly testing there are no operands

    // 6. Function branch token
    function_branch_token->value = "ABS";
    function_branch_token->type = TYPE_TOKEN_FUNCTION;
    function_branch_token->children = malloc(2 * sizeof(formula_token *)); // 2 because sentinel
    function_branch_token->children[0] = number_leaf_token; // TODO: Need to replace this with new tokens to ease test freeing
    function_branch_token->children[1] = leaf_token();

    operation *function_branch_operation = preprocess(&context, function_branch_token);
    munit_assert_not_null(function_branch_operation);
    munit_assert_ushort(PP_OK, ==, function_branch_operation->status);
    munit_assert_ushort(TYPE_NUMBER, ==, function_branch_operation->operands[0]->type);
    munit_assert_ushort(TYPE_SENTINEL, ==, function_branch_operation->operands[1]->type);

    // 7. Binary op branch token
    binary_op_branch_token->value = "+";
    binary_op_branch_token->type = TYPE_TOKEN_BINARY_OPERATOR;
    binary_op_branch_token->children = malloc(2 * sizeof(formula_token *));
    binary_op_branch_token->children[0] = number_leaf_token;
    binary_op_branch_token->children[1] = variable_leaf_token;

    operation *binary_op_branch_operation = preprocess(&context, binary_op_branch_token);
    munit_assert_not_null(binary_op_branch_operation);
    munit_assert_ushort(PP_OK, ==, binary_op_branch_operation->status);
    munit_assert_ushort(TYPE_NUMBER, ==, binary_op_branch_operation->operands[0]->type);
    munit_assert_ushort(TYPE_NUMBER, ==, binary_op_branch_operation->operands[1]->type);

    // 8. Unary op branch token
    unary_op_branch_token->value = "-";
    unary_op_branch_token->type = TYPE_TOKEN_UNARY_OPERATOR;
    unary_op_branch_token->children = malloc(sizeof(formula_token *));
    unary_op_branch_token->children[0] = number_leaf_token;

    operation *unary_op_branch_operation = preprocess(&context, unary_op_branch_token);
    munit_assert_not_null(unary_op_branch_operation);
    munit_assert_ushort(PP_OK, ==, unary_op_branch_operation->status);
    munit_assert_ushort(TYPE_NUMBER, ==, unary_op_branch_operation->operands[0]->type);

    free_token(boolean_leaf_token);
    // free_token(number_leaf_token); déjà free dans un autre free !
    free_token(string_leaf_token);
    // free_token(variable_leaf_token); déjà free dans un autre free !
    free_token(function_leaf_token);
    free_token(function_branch_token);
    free_token(binary_op_branch_token);
    free_token(unary_op_branch_token);
}
#pragma GCC diagnostic pop
