//
// Created by RedNeath on 09/05/2024.
//
#include "../include/munit.h"

// Test functions
#include "number_get_data_test.c"
#include "rate_get_data_test.c"
#include "string_get_data_test.c"
#include "timestamp_get_data_test.c"

// Defining the list of tests to execute:
static MunitTest test_array[] = {
    { "/context/create_context               \t\t", test_create_context, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/create_context_with_variables\t\t", test_create_context_with_variables, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_variable              \t\t", test_insert_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_variables             \t\t", test_insert_variables, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_number_variable   \t\t", test_insert_new_number_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_rate_variable     \t\t", test_insert_new_rate_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_stirng_variable   \t\t", test_insert_new_string_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/insert_new_timestamp_variable\t\t", test_insert_new_timstamp_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/context/get_variable                 \t\t", test_get_variable, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    // Last item must be this one (it is used to identify that this is the end of the list).
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

// Defining the test suite:
static const MunitSuite test_suite = {
    (char *) "",
    test_array,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, "server", argc, argv);
}
