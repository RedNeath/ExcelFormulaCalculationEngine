//
// Created by RedNeath on 16/07/2024.
//
#pragma once
#ifndef ABS_H
#define ABS_H

#include <stdlib.h>
#include "../../processing/pre_processor.h"

extern operand *abs_invoke(operand **input, unsigned long arg_count);
extern unsigned short abs_preprocess(operand **input, unsigned long arg_count);

#endif //ABS_H
