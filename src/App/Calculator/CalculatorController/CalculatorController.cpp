#include "CalculatorController.h"


CalculatorController::CalculatorController(QObject *parent)
{

}

void CalculatorController::setDelay(const int delay)
{
    if (delay != _delay)
        _delay = delay;
}

void CalculatorController::addRequest(const QString request)
{
    QMutexLocker locker(&_mutexRequests);
    _queueRequests.enqueue(request);

    emit signalChangeQueueRequestsSize(_queueRequests.size());
}

QPair<double, int> CalculatorController::getResult()
{
    QMutexLocker locker(&_mutexResults);

    if (!_queueResults.isEmpty())
        return _queueResults.last();
    return QPair<double, int>(0, -2);
}

void CalculatorController::calculate()
{
    _abort = false;
    QString currentRequest("");
    forever
    {

        QCoreApplication::instance()->processEvents();

        if(_abort)
            break;

        _mutexRequests.lock();
        if (!_queueRequests.isEmpty())
        {
            currentRequest = _queueRequests.dequeue();
            emit signalChangeQueueRequestsSize(_queueRequests.size());
        }
        _mutexRequests.unlock();

        if (currentRequest != "")
        {
            QPair<double, int> currentResult = getAnswer(currentRequest);

            QThread::sleep(_delay);

            _mutexResults.lock();
            _queueResults.enqueue(currentResult);
            _mutexResults.unlock();

            emit signalChangeQueueResultsSize(_queueResults.size());

            currentRequest = "";
        }
    }

    emit finished();
}

QPair<double, int> CalculatorController::getAnswer(QString request)
{
    int operationType, errorCode;
    double firstOperand, secondOperand, result;

    //! Преобразуем текущий запрос из строки в тип операции, операнд А и операнд Б
    stringToExpression(operationType, firstOperand, secondOperand, request);

    result = DoIt(operationType, firstOperand, secondOperand, errorCode);

    return QPair<double, int>(result, errorCode);
}
