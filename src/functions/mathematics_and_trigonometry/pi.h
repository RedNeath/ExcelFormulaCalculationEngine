//
// Created by redneath on 16/06/25.
//

#ifndef PI_H
#define PI_H

// Not going further to comply with excel's standards
// See: https://support.microsoft.com/en-us/office/pi-function-264199d0-a3ba-46b8-975a-c4a04608989b
#define PI_VALUE 3.14159265358979

#include "../../processing/pre_processor.h"

extern operand *pi_invoke(operand **input, unsigned long arg_count);
extern unsigned short pi_preprocess(operand **input, unsigned long arg_count);

#endif //PI_H
