#include <iostream>
#include <Matrix.h>

int main() {
    std::string filename;
    std::cout << "Enter filename to read mtx1: ";
    std::cin >> filename;
    auto* mtx = new Matrix(filename);
    std::cout << *mtx << std::endl;
    return 0;
}
