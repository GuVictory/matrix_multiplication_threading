//
// Created by Виктория Губанова on 22.09.2020.
//

#include <thread>
#include "ThreadsWorker.h"

ThreadsWorker::ThreadsWorker() {}

ThreadsWorker::~ThreadsWorker() {}

// Реализация метода для многопоточного перемножения матриц
void ThreadsWorker::multiplyThreading(int numberOfThreads, Matrix &result, const int thread_number, const Matrix &m1, const Matrix &m2) {
    const int matrixSize = m1.getSize();

    const int n_elements = (matrixSize * matrixSize);
    const int n_operations = n_elements / numberOfThreads;
    const int rest_operations = n_elements % numberOfThreads;

    int start_op, end_op;

    if (thread_number == 0) {
        // Первый поток берет на себя большую часть работы
        start_op = n_operations * thread_number;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }
    else {
        start_op = n_operations * thread_number + rest_operations;
        end_op = (n_operations * (thread_number + 1)) + rest_operations;
    }

    for (int op = start_op; op < end_op; ++op) {
        const int row = op % matrixSize;
        const int col = op / matrixSize;
        float r = 0.0f;
        for (int i = 0; i < matrixSize; ++i) {
            const float e1 = m1[row][i];
            const float e2 = m2[i][col];
            r += e1 * e2;
        }

        result[row][col] = r;
    }
}

// Функция для запуска многопоточного умножения матриц
void ThreadsWorker::multithreading_execution(int numberOfThreads, Matrix &r, const Matrix &m1, const Matrix &m2) {
    std::thread threads[numberOfThreads];

    for (int i = 0; i < numberOfThreads; ++i) {
        threads[i] = std::thread(ThreadsWorker::multiplyThreading, numberOfThreads, std::ref(r), i, std::ref(m1), std::ref(m2));
    }

    for (int i = 0; i < numberOfThreads; ++i) {
        threads[i].join();
    }
}


