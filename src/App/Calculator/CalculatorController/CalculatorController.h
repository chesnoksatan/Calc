#ifndef CALCULATORCONTROLLER_H
#define CALCULATORCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QTime>
#include <QQueue>

#include <unistd.h>

#include "../CalcLib/CalcLib.h"

class CalculatorController : public QObject
{
    Q_OBJECT
public:
    explicit CalculatorController(QObject *parent = nullptr);

    void setDelay(const int delay);
    void addRequest(const QString request);
    QPair<double, int> getResult();

signals:
    void signalChangeQueueRequestsSize(const int size);
    void signalChangeQueueResultsSize(const int size);
    void signalAnswerReady();

public slots:
    /*!
     * \brief Основная функция класса
     *        Извлекает из очереди запросов элемент и отправляет его на вычисление
     * \bug В релизной сборке проекта не производит вычислений
     *      Предполагаю, что возникает состояние гонки
     */
    void calculate();

private:
    int _delay = 1;
    QMutex mutex;

    /*!
     * \brief Очередь запросов
     */
    QQueue<QString> QueueRequests;

    /*!
     * \brief Очередь результатов
     *        Каждый элемент представляет собой пару вида: <результат, код ошибки>
     */
    QQueue<QPair<double, int>> QueueResults;

    /*!
     * \brief Функция преобразования строкового запроса в операнды и операцию
     */
    void stringToExpression(int &TypeWork, double &OperandA, double &OperandB,
                            QString request);

    /*!
     * \brief Вызывает функцию внешней библиотеки для вычисления запроса
     *        Добавляет результат вычисления и код ошибки в очередь результатов
     */
    QPair<double, int> getAnswer(QString request);
};

#endif // CALCULATORCONTROLLER_H
