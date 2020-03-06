#include "CalculatorController.h"


CalculatorController::CalculatorController(QObject *parent)
{

}

void CalculatorController::setDelay(const int delay)
{
    _delay = delay;
}

void CalculatorController::addRequest(const QString request)
{
    QMutexLocker locker(&mutex);
    QueueRequests.enqueue(request);

    emit signalChangeQueueRequestsSize(QueueRequests.size());
}

QPair<double, int> CalculatorController::getResult()
{
    QMutexLocker locker(&mutex);

    if (!QueueResults.isEmpty())
        return QueueResults.last();
    return QPair<double, int>(0, -2);
}

void CalculatorController::calculate()
{
    forever {

        QCoreApplication::instance()->processEvents();

        if(_abort)
            break;

        if (!QueueRequests.isEmpty()) {
            sleep(_delay);
            mutex.lock();

            QString currentRequest = QueueRequests.dequeue();

            emit signalChangeQueueRequestsSize(QueueRequests.size());

            QueueResults.enqueue(getAnswer(currentRequest));

            emit signalAnswerReady();
            emit signalChangeQueueResultsSize(QueueResults.size());

            mutex.unlock();
        }
    }

    emit finished();
}

void CalculatorController::stringToExpression(int &TypeWork, double &OperandA,
                                              double &OperandB, QString request)
{
    // Вычислим позицую оператора
    int opPosition = request.indexOf(QRegExp("[-+/*]"));

    // Все символы расположенные левее типа операции - первый операнд
    OperandA = request.left(opPosition).toDouble();
    // Все символы расположенные правее типа операции - второй операнд
    OperandB = request.right(request.length() - opPosition - 1).toDouble();

    if (request.at(opPosition) == '+') TypeWork = Operations::Plus;
    else if (request.at(opPosition) == '-') TypeWork = Operations::Minus;
    else if (request.at(opPosition) == '*') TypeWork = Operations::Multiplication;
    else if (request.at(opPosition) == '/') TypeWork = Operations::Division;
}

QPair<double, int> CalculatorController::getAnswer(QString request)
{
    int operationType, errorCode;
    double firstOperand, secondOperand, result;

    // Преобразуем текущий запрос из строки в тип операции, операнд А и операнд Б
    stringToExpression(operationType, firstOperand, secondOperand, request);

    result = DoIt(operationType, firstOperand, secondOperand, errorCode);

    return QPair<double, int>(result, errorCode);
}
