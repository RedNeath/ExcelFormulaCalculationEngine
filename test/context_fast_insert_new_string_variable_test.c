//
// Created by RedNeath on 28/05/2024.
//
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_fast_insert_new_string_variable(const MunitParameter params[], void *data) {
    formula_context context = create_context(1);

    fast_insert_new_string_variable(&context, "A1", "string");

    munit_assert_ushort(TYPE_STRING, ==, context.variables[0].type);
    munit_assert_string_equal("string", context.variables[0].string_value->value);


    // Checking for sentinel presence
    munit_assert_ushort(TYPE_SENTINEL, ==, context.variables[1].type);
    free_context(&context);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
