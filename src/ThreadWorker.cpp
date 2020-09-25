//
// Created by Виктория Губанова on 25.09.2020.
//

#include <iostream>
#include <thread>
#include "ThreadWorker.h"

/**
 * Статические методы должны быть объявлены вне класса
 */

ThreadWorker* ThreadWorker::pinstance_{nullptr};
int ThreadWorker::numberOfThreads_ = 1;
std::mutex ThreadWorker::mutex_;

ThreadWorker *ThreadWorker::GetInstance(int numberOfThreads)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new ThreadWorker(numberOfThreads);
    }
    return pinstance_;
}

void ThreadWorker::multithreadingOperationExecution(Operations oper, Matrix &result, const Matrix &oper1,
                                                    const Matrix &oper2) {
    std::thread threads[ThreadWorker::numberOfThreads_];

    for (int i = 0; i < ThreadWorker::numberOfThreads_; ++i) {
        // Инициализация каждого потока с функцией умножения только части матрица
        switch (oper) {
            case (Operations::multiplication): {
                threads[i] = std::thread(Matrix::multiplyThreading,
                                         ThreadWorker::numberOfThreads_,
                                         i,
                                         std::ref(result),
                                         std::ref(oper1),
                                         std::ref(oper2)
                );
                break;
            }
            default:
                break;
        }
    }

    for (int i = 0; i < ThreadWorker::numberOfThreads_; ++i) {
        // Ожидание окончания работы всех потоков
        threads[i].join();
    }
}


//template<class T1, class T2, class D1, class D2>
//void
//ThreadWorker::multithreadingExecution(int numberOfParams, void (*op)(int, int, T1, D1, D1), T2 result, D2 mtx1, D2 mtx2) {
//    std::cout << "Thread" << std::endl;
//}


/**
 * // Создаем массив потоков
    std::thread threads[ThreadWorker::numberOfThreads_];


    for (int i = 0; i < ThreadWorker::numberOfThreads_; ++i) {
        // Инициализация каждого потока с функцией умножения только части матрица
        threads[i] = std::thread(op,
                                 ThreadWorker::numberOfThreads_,
                                 i,
                                 std::ref(result),
                                 std::ref(mtx1),
                                 std::ref(mtx2)
                                 );

    }

    for (int i = 0; i < ThreadWorker::numberOfThreads_; ++i) {
        // Ожидание окончания работы всех потоков
        threads[i].join();
    }**/