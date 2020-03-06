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
    QMutexLocker locker(&_mutex);
    _queueRequests.enqueue(request);

    emit signalChangeQueueRequestsSize(_queueRequests.size());
}

QPair<double, int> CalculatorController::getResult()
{
    QMutexLocker locker(&_mutex);

    if (!_queueResults.isEmpty())
        return _queueResults.last();
    return QPair<double, int>(0, -2);
}

void CalculatorController::calculate()
{
    forever {
        _abort = false;

        QCoreApplication::instance()->processEvents();

        if(_abort)
            break;

        if (!_queueRequests.isEmpty()) {
            QThread::sleep(_delay);
            _mutex.lock();

            QString currentRequest = _queueRequests.dequeue();

            emit signalChangeQueueRequestsSize(_queueRequests.size());

            _queueResults.enqueue(getAnswer(currentRequest));

            emit signalAnswerReady();
            emit signalChangeQueueResultsSize(_queueResults.size());

            _mutex.unlock();
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
