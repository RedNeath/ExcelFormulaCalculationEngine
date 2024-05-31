//
// Created by RedNeath on 27/05/2024.
//
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_insert_new_rate_variable(const MunitParameter params[], void *data) {
    formula_context context = create_context(1);

    insert_new_rate_variable(&context, "A1", 0.5);

    munit_assert_ushort(TYPE_RATE, ==, context.variables[0].type);
    munit_assert_float(0.5, ==, context.variables[0].rate_value->value);


    // Checking for sentinel presence
    munit_assert_ushort(TYPE_SENTINEL, ==, context.variables[1].type);
    free_context(&context);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
