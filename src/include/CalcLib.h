#ifndef CALCLIB_H
#define CALCLIB_H

#include "calclib_global.h"

enum Operations
{
    Plus = 0,
    Minus = 1,
    Multiplication = 2,
    Division = 3
};

enum CalculationStatus
{
    Success = 0,
    DivideByZero = -1,
    CalculationError = -2
};

CALCLIBSHARED_EXPORT double DoIt (int TypeWork, double OperandA, double OperandB, int& ErrorCode);

#endif // CALCLIB_H
