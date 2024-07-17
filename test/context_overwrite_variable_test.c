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

    string_variable s = { "A1", "I am a string overwriting an old variable", TYPE_STRING };
    formula_variable new = { NULL, NULL, &s, NULL, TYPE_STRING };

    overwrite_variable(&old, new);

    munit_assert_ushort(TYPE_STRING, ==, old.type);
    munit_assert_null(old.number_value);
    munit_assert_null(old.boolean_value);
    munit_assert_null(old.date_value);
    munit_assert_string_equal("I am a string overwriting an old variable", old.string_value->value);
    munit_assert_string_equal("A1", old.string_value->id);
    munit_assert_ushort(TYPE_STRING, ==, old.string_value->type);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
