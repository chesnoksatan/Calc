#include "CalcLib.h"

double DoIt(int TypeWork, double OperandA, double OperandB, int& ErrorCode)
{
    double ret = 0;
    ErrorCode = CalculationStatus::Success;

    switch (TypeWork)
    {
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

void stringToExpression(int &TypeWork, double &OperandA,
                        double &OperandB, QString request)
{
    //! Вычислим позицую оператора
    int opPosition = request.indexOf(QRegExp("[-+/*^]"));

    //! Все символы расположенные левее типа операции - первый операнд
    OperandA = request.left(opPosition).toDouble();
    //! Все символы расположенные правее типа операции - второй операнд
    OperandB = request.right(request.length() - opPosition - 1).toDouble();

    if (request.at(opPosition) == '+') TypeWork = Operations::Plus;
    else if (request.at(opPosition) == '-') TypeWork = Operations::Minus;
    else if (request.at(opPosition) == '*') TypeWork = Operations::Multiplication;
    else if (request.at(opPosition) == '/') TypeWork = Operations::Division;
}
