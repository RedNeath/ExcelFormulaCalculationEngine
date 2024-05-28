//
// Created by RedNeath on 28/05/2024.
//
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_overwrite_variable(const MunitParameter params[], void *data) {
    number_variable n = { "A1", 10.75, TYPE_NUMBER };
    formula_variable old = { &n, NULL, NULL, NULL, TYPE_NUMBER };

    formula_context context = create_context(1);

    insert_new_number_variable(context, "A1", 10.75);

    formula_variable var = get_variable(context, "A1");

    munit_assert_int(TYPE_NUMBER, ==, var.type);
    munit_assert_float(10.75, ==, var.number_value->value);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
