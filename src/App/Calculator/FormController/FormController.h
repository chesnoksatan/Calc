#ifndef FORMCONTROLLER_H
#define FORMCONTROLLER_H

#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QObject>
#include <QSettings>

#include "CalcLib.h"

class FormController : public QObject
{
    Q_OBJECT
public:
    explicit FormController(QObject *parent = nullptr);

private:
    QQmlApplicationEngine* _engine;
    QObject* _mainWindow;

    QSettings _settings;

    /*!
     * \brief Считывает сохраненые настройки и устанавливает из в форму
     */
    void readSettings();

public slots:
    /*!
     * \brief Вызов происходит в момент закрытия окна программы,
     *        чтобы сохранить последние настройки
     */
    void writeSettings();

    /*!
     * \brief Устанавливает задержку вычислений
     */
    void setDelay(const int delay);

    /*!
     * \brief Получает запрос на вычисление
     */
    void getRequest(const QString request);

    /*!
     * \brief Обновляет размер очереди запросов на форме
     */
    void updateSizeQueueRequests(const int size);

    /*!
     * \brief Обновляет размер очереди результатов на форме
     */
    void updateSizeQueueResults(const int size);

    /*!
     * \brief Создает ответ, исходя из результата и кода ошибки
     *        Отправляет данные вычислений на форму
     */
    void createAnswer(const double calculationResult, const int errorCode);

signals:

    /*!
     * \brief Сигнал добавления записи в консоль
     *        Обрабатывается в qml части приложения
     */
    void signalUpdateConsole(const int errorCode, const QString msg);

    /*!
     * \brief Сигнал добавления нового запроса на вычисление
     */
    void signalSendRequest(const QString request);

    /*!
     * \brief Сигнал установки задержки вычислений
     */
    void signalSetDelay(const int delay);
};

#endif // FORMCONTROLLER_H
