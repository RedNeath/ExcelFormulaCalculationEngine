//
// Created by RedNeath on 28/05/2024.
//
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_fast_insert_variable(const MunitParameter params[], void *data) {
    formula_context context = create_context(1);
    number_variable n = { "A1", 10.75, TYPE_NUMBER };
    formula_variable variable = { &n, NULL, NULL, NULL, TYPE_NUMBER };

    fast_insert_variable(&context, variable);

    munit_assert_ulong(1, ==, context.count);
    munit_assert_ushort(TYPE_NUMBER, ==, context.variables[0].type);
    munit_assert_float(10.75, ==, context.variables[0].number_value->value);


    // Checking for sentinel presence
    munit_assert_ushort(TYPE_SENTINEL, ==, context.variables[1].type);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
