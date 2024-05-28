//
// Created by RedNeath on 23/05/2024.
//

#include "context.h"

formula_context create_context(unsigned long initial_capacity) {
    // Allocating the memory
    formula_variable *variables = malloc((initial_capacity + 1) * sizeof(formula_variable));
    formula_context context = { variables, 0, initial_capacity };

    context.variables[0] = formula_variable_sentinel;

    return context;
}

formula_context create_context_with_variables(unsigned long initial_capacity, formula_variable *variables) {
	formula_context context = create_context(initial_capacity);

	int i;
	for (i = 0; i < initial_capacity; i++) {
		if (variables[i].type == TYPE_SENTINEL) break;
		context.variables[i] = variables[i];
	}

	i++;
	context.count = i;
	context.variables[i] = formula_variable_sentinel;
	return context;
}

void fast_insert_variable(formula_context context, formula_variable variable) {
	if (context.count == context.capacity) {
		// Reallocation needed!
		set_capacity(context, context.capacity + 10); // +10 to have some margin in bad usage cases.
		// If my memory is good, this is the amount the Java ArrayList class uses by default.
	}

	context.variables[context.count] = variable;
	context.count++;
	context.variables[context.count] = formula_variable_sentinel;
}

void fast_insert_variables(formula_context context, formula_variable *variables) {
	int i = 0;
	while (variables[i].type != TYPE_SENTINEL) {
		fast_insert_variable(context, variables[i]);
	}
}

void fast_insert_new_number_variable(formula_context context, char *id, double value) {
	number_variable number = { id, value, TYPE_NUMBER };
	formula_variable variable = { &number, NULL, NULL, NULL, TYPE_NUMBER };

	fast_insert_variable(context, variable);
}

void fast_insert_new_rate_variable(formula_context context, char *id, double value) {
	rate_variable rate = { id, value, TYPE_RATE };
	formula_variable variable = { NULL, &rate, NULL, NULL, TYPE_RATE };

	fast_insert_variable(context, variable);
}

void fast_insert_new_string_variable(formula_context context, char *id, char *value) {
	string_variable str = { id, value, TYPE_STRING }; // Safe variable name (especially for C++ users)
	formula_variable variable = { NULL, NULL, &str, NULL, TYPE_STRING };

	fast_insert_variable(context, variable);
}

void fast_insert_new_date_variable(formula_context context, char *id, unsigned long value) {
	date_variable date = { id, value, TYPE_DATE };
	formula_variable variable = { NULL, NULL, NULL, &date, TYPE_DATE };

	fast_insert_variable(context, variable);
}

void insert_variable(formula_context context, formula_variable variable) {
	char *id;

	switch (variable.type) {
		case TYPE_NUMBER:
			id = variable.number_value->id;
			break;

		case TYPE_RATE:
			id = variable.rate_value->id;
			break;

		case TYPE_STRING:
			id = variable.string_value->id;
			break;

		case TYPE_DATE:
			id = variable.date_value->id;
			break;


		default: // Something went wrong (silent exception thoug...)
			return;
	}

	formula_variable already_existing = get_variable(context, id);
	if (already_existing.type != TYPE_SENTINEL) {
		// It effectively already exists! We need to overwrite it.
		overwrite_variable(already_existing, variable);
	} else {
		fast_insert_variable(context, variable);
	}
}

void insert_variables(formula_context context, formula_variable *variables) {
	int i = 0;
	while (variables[i].type != TYPE_SENTINEL) {
		insert_variable(context, variables[i]);
	}
}

void insert_new_number_variable(formula_context context, char *id, double value) {
	number_variable number = { id, value, TYPE_NUMBER };
	formula_variable variable = { &number, NULL, NULL, NULL, TYPE_NUMBER };

	insert_variable(context, variable);
}

void insert_new_rate_variable(formula_context context, char *id, double value) {
	rate_variable rate = { id, value, TYPE_RATE };
	formula_variable variable = { NULL, &rate, NULL, NULL, TYPE_RATE };

	insert_variable(context, variable);
}

void insert_new_string_variable(formula_context context, char *id, char *value) {
	string_variable str = { id, value, TYPE_STRING }; // Safe variable name (especially for C++ users)
	formula_variable variable = { NULL, NULL, &str, NULL, TYPE_STRING };

	insert_variable(context, variable);
}

void insert_new_date_variable(formula_context context, char *id, unsigned long value) {
	date_variable date = { id, value, TYPE_DATE };
	formula_variable variable = { NULL, NULL, NULL, &date, TYPE_DATE };

	insert_variable(context, variable);
}


formula_variable get_variable(formula_context context, char *id) {
	// Simple sequential search, as for now (see the usage tips in the main readme.md file)
	formula_variable variable;

	for (int i = 0; i < context.count; i++) {
		variable = context.variables[i];

		switch (variable.type) {
			case TYPE_NUMBER:
				if (variable.number_value->id == id) return variable;
				break;
			case TYPE_RATE:
				if (variable.rate_value->id == id) return variable;
				break;
			case TYPE_STRING:
				if (variable.string_value->id == id) return variable;
				break;
			case TYPE_DATE:
				if (variable.date_value->id == id) return variable;
				break;

			default: // Reached end of list (wrong count) or altered data!
				return formula_variable_sentinel;
		}
	}

	return formula_variable_sentinel;
}

void set_capacity(formula_context context, unsigned long new_capacity) {
	formula_variable *variables = malloc((new_capacity + 1) * sizeof(formula_variable));

	// Transfer the functions to the new array
	int i = 0;
	while (context.variables[i].type != TYPE_SENTINEL && i < new_capacity) { // Second condition in case we reduce
		variables[i] = context.variables[i];
	}

	free(context.variables);
	context.variables = variables;
}

void overwrite_variable(formula_variable old_variable, formula_variable new_variable) {
	old_variable.number_value = new_variable.number_value;
	old_variable.rate_value = new_variable.rate_value;
	old_variable.string_value = new_variable.string_value;
	old_variable.date_value = new_variable.date_value;

	old_variable.type = new_variable.type;
}

void free_context(formula_context context) {
	free(context.variables);
	// End of the story for the context 💁‍♂️❤️
}
