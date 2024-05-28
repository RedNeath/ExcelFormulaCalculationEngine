//
// Created by RedNeath on 28/05/2024.
//
#include "../src/context.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_free_context(const MunitParameter params[], void *data) {
    formula_context context = create_context(1);

    insert_new_number_variable(context, "A1", 10.75);

    free_context(context);
    return MUNIT_OK;
}
#pragma GCC diagnostic pop
