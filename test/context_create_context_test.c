//
// Created by RedNeath on 23/05/2024.
//
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_create_context(const MunitParameter params[], void *data) {
    formula_context context = create_context(10);

    // Logically, the context should have one formula_variable, which is a sentinel
    formula_variable sentinel = context.variables[0];
    munit_assert_int(TYPE_SENTINEL, ==, sentinel.type);

    return MUNIT_OK;
}
#pragma GCC diagnostic pop
