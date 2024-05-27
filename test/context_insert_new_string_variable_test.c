//
// Created by Xiaomi on 27/05/2024.
//
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_insert_new_string_variable(const MunitParameter params[], void *data) {
    formula_context context = create_context(1);

    insert_new_string_variable(context, "A1", "string");

    munit_assert_int(TYPE_STRING, ==, context.variables[0].type);
    munit_assert_string_equal("string", context.variables[0].string_value->value);


    // Checking for sentinel presence
    munit_assert_int(TYPE_SENTINEL, ==, context.variables[1].type);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
