//
// Created by RedNeath on 01/07/2024.
//
#include "../src/parser.h"
#include "../include/munit.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
static MunitResult test_parse_number(const MunitParameter params[], void *data) {
    char *integer_number = "1";
    char *floating_number = "1.02";
    char *not_a_number = "not a number";
    char *a;

    formula_token *token =
}
#pragma GCC diagnostic pop
