#include "FormController.h"

FormController::FormController(QObject *parent) : QObject(parent)
{
    _engine = new QQmlApplicationEngine;

    _engine->rootContext()->setContextProperty("FormController", this);

    QQmlComponent component(_engine, QUrl("../../../export/qml/main.qml"));
    _mainWindow = component.create();

    readSettings();
}

void FormController::setDelay(const int delay)
{
    emit signalSetDelay(delay);
}

void FormController::getRequest(const QString request)
{
    emit signalSendRequest(request);
}

void FormController::createAnswer(const double calculationResult, const int errorCode)
{
    switch (errorCode)
    {
    case CalculationStatus::Success:
        signalUpdateConsole(CalculationStatus::Success, QString::number(calculationResult));
        break;
    case CalculationStatus::DivideByZero:
        signalUpdateConsole(CalculationStatus::DivideByZero, QString("Деление на 0"));
        break;
    case CalculationStatus::CalculationError:
        signalUpdateConsole(CalculationStatus::CalculationError, QString("Ошибка вычислений"));
        break;
    default:
        break;
    }
}

void FormController::updateSizeQueueRequests(const int size)
{
    QObject* QueueRequestsSize = _mainWindow->findChild<QObject*>("QueueRequests");
    if (QueueRequestsSize)
        QueueRequestsSize->setProperty("text", size);
}

void FormController::updateSizeQueueResults(const int size)
{
    QObject* QueueResultsSize = _mainWindow->findChild<QObject*>("QueueResults");
    if (QueueResultsSize)
        QueueResultsSize->setProperty("text", size);
}

void FormController::readSettings()
{
    _settings.beginGroup("/Settings");

        _settings.beginGroup("/Size");
            _mainWindow->setProperty("width", _settings.value("/width",400).toInt());
            _mainWindow->setProperty("height", _settings.value("/height",600).toInt());
        _settings.endGroup();

        _settings.beginGroup("/Position");
            _mainWindow->setProperty("x", _settings.value("/x",0).toInt());
            _mainWindow->setProperty("y", _settings.value("/y",0).toInt());
        _settings.endGroup();

    _settings.endGroup();
}

void FormController::writeSettings()
{
    _settings.beginGroup("/Settings");

        _settings.beginGroup("/Size");
            _settings.setValue("/width", _mainWindow->property("width"));
            _settings.setValue("/height", _mainWindow->property("height"));
        _settings.endGroup();

        _settings.beginGroup("/Position");
            _settings.setValue("/x", _mainWindow->property("x"));
            _settings.setValue("/y", _mainWindow->property("y"));
        _settings.endGroup();

    _settings.endGroup();
}
