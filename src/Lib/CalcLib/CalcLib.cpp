#include "CalcLib.h"

double DoIt(int TypeWork, double OperandA, double OperandB, int& ErrorCode)
{
    double ret = 0;
    ErrorCode = CalculationStatus::Success;

    switch (TypeWork) {
    // Plus
    case Operations::Plus:
        ret = OperandA + OperandB;
        break;
    // Minus
    case Operations::Minus:
        ret = OperandA - OperandB;
        break;
    // Multiplication
    case Operations::Multiplication:
        ret = OperandA * OperandB;
        break;
    // Division
    case Operations::Division:
        if (OperandB == 0) ErrorCode = CalculationStatus::DivideByZero;
        else ret = OperandA / OperandB;
        break;
    default:
        ErrorCode = CalculationStatus::CalculationError;
        break;
    }

    return ret;
}
