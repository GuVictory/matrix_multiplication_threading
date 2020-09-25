//
// Created by Виктория Губанова on 25.09.2020.
//

#ifndef MATRIX_MULTIPLICATION_THREADING_THREADWORKER_H
#define MATRIX_MULTIPLICATION_THREADING_THREADWORKER_H

#include <mutex>
#include <Matrix.h>
#include <Operations.h>

/**
 * Класс для работы с потоками будет обладать свойством паттерна одиночка, который
 * предоставляет метод `GetInstance`, который ведёт себя как
 * альтернативный конструктор и позволяет клиентам получать один и тот же
 * экземпляр класса при каждом вызове.
 */

class ThreadWorker {
    /**
     * Конструктор Одиночки всегда должен быть скрытым, чтобы предотвратить
     * создание объекта через оператор new.
     */
private:
    static ThreadWorker * pinstance_;
    static std::mutex mutex_;
    static int numberOfThreads_;

protected:
    ThreadWorker(int numberOfThreads)
    {
        ThreadWorker::numberOfThreads_ = numberOfThreads;
    }

    ~ThreadWorker() {}

public:
    /**
     * Одиночки не должны быть клонируемыми.
     */
    ThreadWorker(ThreadWorker &other) = delete;

    /**
     * Так же нет доступа к оператору присваивания
     */
    void operator=(const ThreadWorker &) = delete;

    /**
     * Это статический метод, управляющий доступом к экземпляру одиночки. При
     * первом запуске, он создаёт экземпляр одиночки и помещает его в
     * статическое поле. При последующих запусках, он возвращает клиенту объект,
     * хранящийся в статическом поле.
     */
    static ThreadWorker *GetInstance(int numberOfThreads);

    /**
     * Реализация логики выполнения разных операций с матрицами в многопоточном режиме
     * oper - отвечает за тип операции (+, -, *) (реализовано умножение)
     */
    static void multithreadingOperationExecution(Operations oper, Matrix& result, const Matrix& oper1, const Matrix& oper2);

    static int getNumberOfThreads() {
        return ThreadWorker::numberOfThreads_;
    }
};


#endif //MATRIX_MULTIPLICATION_THREADING_THREADWORKER_H
