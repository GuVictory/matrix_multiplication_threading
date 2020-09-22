#include <iostream>
#include <Matrix.h>
#include <ThreadsWorker.h>
#include <ctime>

int main() {
    std::clock_t start;
    double durationSingle, durationMult;
    int numberOfThreads = 1;

    std::string filename;
    std::cout << "Enter filename to read mtx1: ";
    std::cin >> filename;
    auto* mtx1 = new Matrix(filename);

    std::cout << "Enter filename to read mtx2: ";
    std::cin >> filename;
    auto* mtx2 = new Matrix(filename);

    std::cout << "Matrix 1: " << std::endl;
    std::cout << *mtx1 << std::endl;

    std::cout << "Matrix 2: " << std::endl;
    std::cout << *mtx2 << std::endl;

    std::cout << "Enter numberOfThreads: ";
    std::cin >> numberOfThreads;

    start = std::clock();
    auto resMtx1 = *mtx1 * *mtx2;
    durationSingle = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    auto* thWorker = new ThreadsWorker();
    auto* resultMtx = new Matrix(mtx1->getSize());

    start = std::clock();
    thWorker->multithreading_execution(numberOfThreads, *resultMtx, *mtx1, *mtx2);
    durationMult = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "Matrix1 * Matrix2: " << std::endl;
    std::cout << resMtx1 << std::endl;

    std::cout << "resultMtx: " << std::endl;
    std::cout << *resultMtx << std::endl;

    std::cout<<"durationSingle: "<< durationSingle <<'\n';
    std::cout<<"durationMult: "<< durationMult <<'\n';

    return 0;
}
