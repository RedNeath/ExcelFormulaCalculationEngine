//
// Created by RedNeath on 28/05/2024.
//
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_fast_insert_new_boolean_variable(const MunitParameter params[], void *data) {
    formula_context context = create_context(1);

    fast_insert_new_boolean_variable(&context, "A1", true);

    munit_assert_ushort(TYPE_BOOLEAN, ==, context.variables[0].type);
    munit_assert_true(context.variables[0].boolean_value->value);


    // Checking for sentinel presence
    munit_assert_ushort(TYPE_SENTINEL, ==, context.variables[1].type);
    free_context(&context);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
