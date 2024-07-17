//
// Created by RedNeath on 27/05/2024.
//
#include <time.h>
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_insert_variables(const MunitParameter params[], void *data) {
    formula_context context = create_context(2);
    number_variable *n = malloc(sizeof(number_variable));
    n->id = "A1";
    n->value = 10.75;
    n->type = TYPE_NUMBER;

    boolean_variable *b = malloc(sizeof(boolean_variable));
    b->id = "A2";
    b->value = false;
    b->type = TYPE_BOOLEAN;

    formula_variable v1 = { n, NULL, NULL, NULL, TYPE_NUMBER };
    formula_variable v2 = { NULL, b, NULL, NULL, TYPE_BOOLEAN };
    formula_variable *variables = malloc(5 * sizeof(formula_variable));
    variables[0] = v1;
    variables[1] = v2;

    insert_variables(&context, variables);

    munit_assert_ushort(TYPE_NUMBER, ==, context.variables[0].type);
    munit_assert_float(10.75, ==, context.variables[0].number_value->value);

    munit_assert_ushort(TYPE_BOOLEAN, ==, context.variables[1].type);
    munit_assert_false(context.variables[1].boolean_value->value);


    // Checking for sentinel presence
    munit_assert_ushort(TYPE_SENTINEL, ==, context.variables[2].type);
    free_context(&context);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
