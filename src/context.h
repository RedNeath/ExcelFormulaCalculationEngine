//
// Created by Xiaomi on 23/05/2024.
//

#ifndef CONTEXT_H
#define CONTEXT_H

/* types */
#define TYPE_NUMBER 0
#define TYPE_RATE 1
#define TYPE_STRING 2
#define TYPE_DATE 3
#define TYPE_SENTINEL -1

/* structures */
typedef struct number_variable number_variable;
typedef struct rate_variable rate_variable;
typedef struct string_variable string_variable;
typedef struct date_variable date_variable;
typedef struct formula_variable formula_variable;
typedef struct formula_context formula_context;

struct number_variable {
    char *id;
    float value;
    unsigned short type;
}

struct rate_variable {
    char *id;
    float value;
    unsigned short type;
}

struct string_variable {
    char *id;
    char *value;
    unsigned short type;
}

struct date_variable {
    char *id;
    unsigned long value;
    unsigned short type;
}


struct formula_variable {
    number_variable *number_value;
    rate_variable *rate_value;
    string_variable *string_value;
    date_variable *date_value;

    unsigned short type;
}

struct formula_context {
    formula_variable *variables;
}

/* functions */
/**
 * Create a context with a given initial capacity.
 *
 * > **NOTE:**
 * > As memory is allocated within the context creation, it should be freed later on!
 *
 * @param unsigned long initial_capacity The initial capacity to allocate. If you add more variables
 * than the initial capacity, note that memory will have to be reallocated and data moved to that new
 * place, which is very costful, especially on large amounts of data!
 * @return formula_context The corresponding context.
 */
extern formula_context create_context(unsigned long initial_capacity);
/**
 * Create a context prefilled with a list of variables.
 *
 * > **NOTE:**
 * > As memory is allocated within the context creation, it should be freed later on!
 *
 * @param unsigned long initial_capacity The initial capacity to allocate. If you add more variables
 * than the initial capacity, note that memory will have to be reallocated and data moved to that new
 * place, which is very costful, especially on large amounts of data! Also, if there are more variables
 * in the list you provide than the capacity you specify, the list of variables you give will be
 * cropped to that new size.
 * @param formula_variable *variables The list of variables to add straight to the list.
 * @return formula_context The corredsponding context.
 */
extern formula_context create_context_with_variables(unsigned long initial_capacity, formula_variable *variables);

/**
 * Insert a variable into a given context.
 *
 * > **NOTE:**
 * > Adding more variables than the context can contain will result in a reallocation and movement
 * > of the variables in memory, which can be very costful with large amounts of data!
 * >
 * > Please, be careful when chosing your initial capacity!
 *
 * > **OTHER NOTE:**
 * > When you insert a formula variable in the context, consider you lose ownership of memory to
 * > all its value. That means that its memory should be freed when freeing the context!
 *
 * @param formula_context context The context in which the variable should be added.
 * @param formula_variable variable The variable to add to the context.
 */
extern void insert_variable(formula_context context, formula_variable variable);
/**
 * Insert a bunch of variables into a given context.
 *
 * > **NOTE:**
 * > Adding more variables than the context can contain will result in a reallocation and movement
 * > of the variables in memory, which can be very costful with large amounts of data!
 * >
 * > Please, be careful when chosing your initial capacity!
 *
 * > **OTHER NOTE:**
 * > When you insert a formula variable in the context, consider you lose ownership of memory to
 * > all its value. That means that its memory should be freed when freeing the context!
 *
 * @param formula_context context The context in which the variables should be added.
 * @param formula_variable *variables The list of variables to add to the context.
 */
extern void insert_variables(formula_context context, formula_variable *variables);

/**
 * Insert a new number typed variable to the context. This will allocate the memory and create the
 * variable for you.
 *
 * > **NOTE:**
 * > Adding more variables than the context can contain will result in a reallocation and movement
 * > of the variables in memory, which can be very costful with large amounts of data!
 * >
 * > Please, be careful when chosing your initial capacity!
 *
 * > **OTHER NOTE:**
 * > This function allocates memory for you, thus, it should be freed when freeing the context!
 *
 * @param formula_context context The context in which the number variable shoudl be added.
 * @param char *id The id of the variable, allowing you to name it in the formula
 * @param float value The numeric value of the variable.
 */
extern void insert_new_number_variable(formula_context context, char *id, float value);
/**
 * Insert a new rate typed variable to the context. This will allocate the memory and create the
 * variable for you.
 *
 * > **NOTE:**
 * > Adding more variables than the context can contain will result in a reallocation and movement
 * > of the variables in memory, which can be very costful with large amounts of data!
 * >
 * > Please, be careful when chosing your initial capacity!
 *
 * > **OTHER NOTE:**
 * > This function allocates memory for you, thus, it should be freed when freeing the context!
 *
 * @param formula_context context The context in which the rate variable shoudl be added.
 * @param char *id The id of the variable, allowing you to name it in the formula
 * @param float value The rate value of the variable.
 */
extern void insert_new_rate_variable(formula_context context, char *id, float value);
/**
 * Insert a new string typed variable to the context. This will allocate the memory and create the
 * variable for you.
 *
 * > **NOTE:**
 * > Adding more variables than the context can contain will result in a reallocation and movement
 * > of the variables in memory, which can be very costful with large amounts of data!
 * >
 * > Please, be careful when chosing your initial capacity!
 *
 * > **OTHER NOTE:**
 * > This function allocates memory for you, thus, it should be freed when freeing the context!
 *
 * @param formula_context context The context in which the string variable shoudl be added.
 * @param char *id The id of the variable, allowing you to name it in the formula
 * @param float value The string value of the variable.
 */
extern void insert_new_string_variable(formula_context context, char *id, char *value);
/**
 * Insert a new date typed variable to the context. This will allocate the memory and create the
 * variable for you.
 *
 * > **NOTE:**
 * > Adding more variables than the context can contain will result in a reallocation and movement
 * > of the variables in memory, which can be very costful with large amounts of data!
 * >
 * > Please, be careful when chosing your initial capacity!
 *
 * > **OTHER NOTE:**
 * > This function allocates memory for you, thus, it should be freed when freeing the context!
 *
 * @param formula_context context The context in which the date variable shoudl be added.
 * @param char *id The id of the variable, allowing you to name it in the formula
 * @param float value The date value of the variable (as a UNIX epoch).
 */
extern void insert_new_date_variable(formula_context context, char *id, unsigned long value);

/**
 * Allows you to retreive a variable from a given id, if it exists in the context.
 *
 * @param formula_context context The context in which the variable should be looked for.
 * @param char *id The ID of the variable.
 * @return The corresponding formula_variable, or the sentinel if it wasn't found.
 */
extern formula_variable get_variable(formula_context context, char *id);

#endif //CONTEXT_H
