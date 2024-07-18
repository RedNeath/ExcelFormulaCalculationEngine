//
// Created by P15v on 16/07/2024.
//

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "pre_processor.h"

extern operand *process_negation(operand **input);
extern operand *process_percent(operand **input);
extern operand *process_power(operand **input);
extern operand *process_multiplication(operand **input);
extern operand *process_division(operand **input);
extern operand *process_addition(operand **input);
extern operand *process_subtraction(operand **input);
extern operand *process_concatenation(operand **input);
extern operand *process_equality(operand **input);
extern operand *process_strict_superiority(operand **input);
extern operand *process_strict_inferiority(operand **input);
extern operand *process_superiority(operand **input);
extern operand *process_inferiority(operand **input);
extern operand *process_difference(operand **input);

#endif //PROCESSOR_H
