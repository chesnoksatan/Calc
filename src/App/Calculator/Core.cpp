#include "Core.h"

Core::Core(QObject *parent) : QObject(parent)
{
    _form = new FormController();

    _calcController = new CalculatorController();
    _calcThread = new QThread();

    startThread();

    QObject::connect(_form, &FormController::signalSendRequest,
                     this, &Core::slotGetRequest);

    QObject::connect(_form, &FormController::signalSetDelay,
                     this, &Core::slotGetDelay);

    QObject::connect(this, &Core::signalSendResult,
                     _form, &FormController::createAnswer);

    QObject::connect(_calcController, &CalculatorController::signalChangeQueueRequestsSize,
                     _form, &FormController::updateSizeQueueRequests);

    QObject::connect(_calcController, &CalculatorController::signalAnswerReady,
                     this, &Core::slotGetResult);

    QObject::connect(_calcController, &CalculatorController::signalChangeQueueResultsSize,
                     _form, &FormController::updateSizeQueueResults);

}

Core::~Core()
{
    _calcThread->quit();

    delete _calcThread;
    delete _calcController;
    delete _form;
}

void Core::slotGetDelay(const int delay)
{
    _calcController->setDelay(delay);
}

void Core::slotGetRequest(const QString request)
{
    _calcController->addRequest(request);
}

void Core::slotGetResult()
{
    QPair<double, int> result = _calcController->getResult();
    emit signalSendResult(result.first, result.second);
}

void Core::startThread()
{
    _calcController->moveToThread(_calcThread);

    QObject::connect(_calcThread, &QThread::started,
                     _calcController, &CalculatorController::calculate);

    QObject::connect(_calcController, &CalculatorController::destroyed,
                     _calcThread, &QThread::quit);

    _calcThread->start();
}
