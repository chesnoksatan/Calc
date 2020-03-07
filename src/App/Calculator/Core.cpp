#include "Core.h"

Core::Core(QObject *parent) : QObject(parent)
{
    _form = new FormController();

    _calcController = new CalculatorController();
    _calcThread = new QThread();

    startThread();

    //! сигнла-слот добавления запроса
    QObject::connect(_form, &FormController::signalSendRequest,
                     this, &Core::slotGetRequest);

    //! сигнла-слот установки задержки вычислений
    QObject::connect(_form, &FormController::signalSetDelay,
                     this, &Core::slotGetDelay);

    //! сигнла-слот отправки результата на форму
    QObject::connect(this, &Core::signalSendResult,
                     _form, &FormController::createAnswer);

    //! сигнла-слот изменения размера очереди запросов на форме
    QObject::connect(_calcController, &CalculatorController::signalChangeQueueRequestsSize,
                     _form, &FormController::updateSizeQueueRequests);

    //! сигнла-слот изменения размера очереди результатов на форме
    QObject::connect(_calcController, &CalculatorController::signalChangeQueueResultsSize,
                     _form, &FormController::updateSizeQueueResults);

    //! сигнла-слот получения результата вычислений
    QObject::connect(_calcController, &CalculatorController::signalChangeQueueResultsSize,
                     this, &Core::slotGetResult);
}

Core::~Core()
{
    if (_calcThread->isRunning())
    {
        _calcController->abort();
        _calcThread->quit();
        _calcThread->wait();
    }

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
    //! Прочитаем последний добавленный в очередь результат и передадим его в форму
    QPair<double, int> result = _calcController->getResult();
    emit signalSendResult(result.first, result.second);
}

void Core::startThread()
{
    _calcController->moveToThread(_calcThread);

    //! В момент запуска второстепенного потока вызвается функция calculate
    QObject::connect(_calcThread, &QThread::started,
                     _calcController, &CalculatorController::calculate);

    //! При завершении работы функции calculate потоку передается сигнал finished,
    //! который вызывает срабатывание слота quit
    QObject::connect(_calcController, &CalculatorController::finished,
                     _calcThread, &QThread::quit);

    _calcThread->start();
}
