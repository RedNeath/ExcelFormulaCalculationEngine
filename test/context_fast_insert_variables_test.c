//
// Created by RedNeath on 28/05/2024.
//
#include <time.h>
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_fast_insert_variables(const MunitParameter params[], void *data) {
    formula_context context = create_context(2);
    number_variable *n = malloc(sizeof(number_variable));
    n->id = "A1";
    n->value = 10.75;
    n->type = TYPE_NUMBER;

    rate_variable *r = malloc(sizeof(rate_variable));
    r->id = "A2";
    r->value = 0.5;
    r->type = TYPE_RATE;

    formula_variable v1 = { n, NULL, NULL, NULL, TYPE_NUMBER };
    formula_variable v2 = { NULL, r, NULL, NULL, TYPE_RATE };
    formula_variable *variables = malloc(5 * sizeof(formula_variable));
    variables[0] = v1;
    variables[1] = v2;
    variables[2] = formula_variable_sentinel;

    fast_insert_variables(&context, variables);
    free(variables);

    munit_assert_ulong(2, ==, context.count);

    munit_assert_ushort(TYPE_NUMBER, ==, context.variables[0].type);
    munit_assert_float(10.75, ==, context.variables[0].number_value->value);

    munit_assert_ushort(TYPE_RATE, ==, context.variables[1].type);
    munit_assert_float(0.5, ==, context.variables[1].rate_value->value);


    // Checking for sentinel presence
    munit_assert_ushort(TYPE_SENTINEL, ==, context.variables[2].type);
    free_context(&context);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
