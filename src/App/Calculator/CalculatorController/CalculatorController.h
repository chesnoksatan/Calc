#ifndef CALCULATORCONTROLLER_H
#define CALCULATORCONTROLLER_H

#include <QObject>
#include <QMutex>
#include <QQueue>
#include <QCoreApplication>
#include <QThread>

#include "CalcLib.h"

class CalculatorController : public QObject
{
    Q_OBJECT
public:
    explicit CalculatorController(QObject *parent = nullptr);

    /*!
     *   \brief Установка задержки вычислений
     */
    void setDelay(const int delay);

    /*!
     *   \brief Добавить в очередь запросов новый запрос
     */
    void addRequest(const QString request);

    /*!
     *   \brief Прочитать последний результат вычислений
     */
    QPair<double, int> getResult();

    /*!
     *   \brief Прекращение работы потока
     */
    void abort() { _abort = true; }

signals:

    /*!
     *   \brief Сигнал изменения размеров очереди запросов
     */
    void signalChangeQueueRequestsSize(const int size);

    /*!
     *   \brief Сигнал изменения размеров очереди результатов
     */
    void signalChangeQueueResultsSize(const int size);

    /*!
     *   \brief Сигнал прекращение завершения потока
     */
    void finished();

public slots:
    /*!
     * \brief Основная функция класса
     *        Извлекает из очереди запросов элемент и отправляет его на вычисление
     */
    void calculate();

private:
    int _delay = 1; ///< Количество секунд задержки вычислений

    QMutex _mutexRequests; ///< Мьютекс для очереди запросов
    QMutex _mutexResults; ///< Мьютекс для очереди результатов

    std::atomic<bool> _abort; ///< Флаг прекращения потока

    QQueue<QString> _queueRequests; ///< Очередь запросов

    QQueue<QPair<double, int>> _queueResults; ///< Очередь результатов

    /*!
     * \brief Вызывает функцию внешней библиотеки для вычисления запроса
     *        Добавляет результат вычисления и код ошибки в очередь результатов
     */
    QPair<double, int> getAnswer(QString request);
};

#endif // CALCULATORCONTROLLER_H
