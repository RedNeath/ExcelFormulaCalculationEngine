//
// Created by RedNeath on 27/05/2024.
//
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_insert_new_date_variable(const MunitParameter params[], void *data) {
    formula_context context = create_context(1);

    insert_new_date_variable(&context, "A1", 1716809092);

    munit_assert_ushort(TYPE_DATE, ==, context.variables[0].type);
    munit_assert_ulong(1716809092, ==, context.variables[0].date_value->value);


    // Checking for sentinel presence
    munit_assert_ushort(TYPE_SENTINEL, ==, context.variables[1].type);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
