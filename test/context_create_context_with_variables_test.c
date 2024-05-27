//
// Created by Xiaomi on 27/05/2024.
//
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_create_context_with_variables(const MunitParameter params[], void *data) {
    number_variable n1 = { "A1", 10, TYPE_NUMBER };
    rate_variable r = { "A2", 0.2, TYPE_RATE };
    string_variable s = { "A3", "string", TYPE_STRING };
    date_variable d = { "A4", 1716809092, TYPE_DATE };
    number_variable n2 = { "A5", 12.12, TYPE_NUMBER };

    formula_variable v1 = { &n1, NULL, NULL, NULL, TYPE_NUMBER };
    formula_variable v2 = { NULL, &r, NULL, NULL, TYPE_NUMBER };
    formula_variable v3 = { NULL, NULL, &s, NULL, TYPE_NUMBER };
    formula_variable v4 = { NULL, NULL, NULL, &d, TYPE_NUMBER };
    formula_variable v5 = { &n2, NULL, NULL, NULL, TYPE_NUMBER };

    formula_variable *variables = malloc(5 * sizeof(formula_variable));
    variables[0] = v1;
    variables[1] = v2;
    variables[2] = v3;
    variables[3] = v4;
    variables[4] = v5;

    formula_context context = create_context_with_variables(5, variables);

    munit_assert_int(TYPE_NUMBER, ==, context.variables[0].type);
    munit_assert_float(10, ==, context.variables[0].number_value->value);

    munit_assert_int(TYPE_RATE, ==, context.variables[1].type);
    munit_assert_float(0.2, ==, context.variables[1].rate_value->value);

    munit_assert_int(TYPE_STRING, ==, context.variables[2].type);
    munit_assert_string_equal("string", context.variables[2].string_value->value);

    munit_assert_int(TYPE_DATE, ==, context.variables[3].type);
    munit_assert_ulong(1716809092, ==, context.variables[3].date_value->value);

    munit_assert_int(TYPE_NUMBER, ==, context.variables[4].type);
    munit_assert_float(12.12, ==, context.variables[4].number_value->value);


    // Checking for sentinel presence
    munit_assert_int(TYPE_SENTINEL, ==, context.variables[5].type);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
