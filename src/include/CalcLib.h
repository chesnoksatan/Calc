#ifndef CALCLIB_H
#define CALCLIB_H

#include "calclib_global.h"
#include <QString>
#include <QRegExp>

/*!
 *  \brief Перечисление возможных операций
 */
enum Operations
{
    Plus = 0,
    Minus = 1,
    Multiplication = 2,
    Division = 3,
};

/*!
 *  \brief Перечисление состояний вычисления
 */
enum CalculationStatus
{
    Success = 0,
    DivideByZero = -1,
    CalculationError = -2
};

/*!
 *  \brief Функция вычисления запроса
 */
CALCLIBSHARED_EXPORT double DoIt (int TypeWork, double OperandA, double OperandB,
                                  int& ErrorCode);
/*!
 *  \brief Функция преобразования строкового запроса в операнды и операцию
 */
CALCLIBSHARED_EXPORT void stringToExpression(int &TypeWork, double &OperandA,
                                             double &OperandB, QString request);

#endif // CALCLIB_H
