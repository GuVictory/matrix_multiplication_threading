#include <iostream>
#include <Matrix.h>

int main() {
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

    std::cout << "Matrix1 * Matrix2: " << std::endl;
    auto* resMtx = new Matrix(*mtx1 * *mtx2);
    std::cout << *mtx1 * *mtx2 << std::endl;
    return 0;
}
