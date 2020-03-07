#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QThread>

#include "FormController/FormController.h"
#include "CalculatorController/CalculatorController.h"

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QObject *parent = nullptr);
    ~Core();

signals:

    /*!
     * \brief Сигнал добавления нового запроса на вычисление
     */
    void signalSendResult(const double result, const int errorCode);

private:
    FormController* _form;
    CalculatorController* _calcController;

    QThread* _calcThread;

    void startThread();

public slots:
    /*!
     * \brief Перехватывает сигнал на установку задержки вычислений
     * \param delay {int} задержка вычислений в секундах
     */
    void slotGetDelay(const int delay);

    /*!
     * \brief Добавляет в очередь запросов новый элемент
     * \param request {QString} запрос пользователя
     */
    void slotGetRequest(const QString request);

    /*!
     * \brief Извлекает из очереди результатов элемент
     *        и отправляет на форму
     */
    void slotGetResult();

};

#endif // CORE_H
