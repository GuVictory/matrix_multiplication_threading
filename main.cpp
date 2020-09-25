#include <iostream>
#include <Matrix.h>
#include <ThreadWorker.h>
#include <ctime>
#include <fstream>


int main() {
    int numberOfThreads = 0;
    std::string filename;

    std::cout << "Введите количество потоков: ";
    std::cin >> numberOfThreads;

    // Инициализируем сущность класса ThreadWorker с определенным количеством потоков
    ThreadWorker::GetInstance(numberOfThreads);

    std::cout << "Введите имя файла для чтения 1й матрицы: ";
    std::cin >> filename;
    auto* mtx1 = new Matrix(filename);

    std::cout << "Введите имя файла для чтения 2й матрицы: ";
    std::cin >> filename;
    auto* mtx2 = new Matrix(filename);



    // Произведем простое перемножение матриц
    auto resultMtx = *mtx1 * *mtx2;

    // Результаты умножения запишем в файл
    std::ofstream out("data/result.txt");
    out << resultMtx << std::endl;


    return 0;
}
