//
// Created by Виктория Губанова on 22.09.2020.
//

#ifndef MATRIX_MULTIPLICATION_THREADING_THREADSWORKER_H
#define MATRIX_MULTIPLICATION_THREADING_THREADSWORKER_H

#include <Matrix.h>

class ThreadsWorker {
private:
    static void multiplyThreading(int numberOfThreads, Matrix& result, const int thread_number, const Matrix& m1, const Matrix& m2);
public:
    ThreadsWorker();
    ~ThreadsWorker();

    void multithreading_execution(int numberOfThreads, Matrix& r, const Matrix& m1, const Matrix& m2);
};


#endif //MATRIX_MULTIPLICATION_THREADING_THREADSWORKER_H
