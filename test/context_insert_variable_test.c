//
// Created by Xiaomi on 27/05/2024.
//
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_insert_variable(const MunitParameter params[], void *data) {
    formula_context context = create_context(1);
    number_variable n = { "A1", 10.75, TYPE_NUMBER };
    formula_variable variable = { &n, NULL, NULL, NULL, TYPE_NUMBER };

    insert_variable(context, variable);

    munit_assert_int(TYPE_NUMBER, ==, context.variables[0].type);
    munit_assert_float(10.75, ==, context.variables[0].number_value->value);


    // Checking for sentinel presence
    munit_assert_int(TYPE_SENTINEL, ==, context.variables[1].type);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop