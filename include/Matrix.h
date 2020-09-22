//
// Created by Виктория Губанова on 22.09.2020.
//

#ifndef MATRIX_MULTIPLICATION_THREADING_MATRIX_H
#define MATRIX_MULTIPLICATION_THREADING_MATRIX_H

#include <vector>
#include <iostream>

class Matrix {
private:
    std::vector<std::vector<int>> matrix;
public:
    Matrix();
    explicit Matrix(int size);
    explicit Matrix(const std::string& filename);
    Matrix(const Matrix& mtx);
    ~Matrix();



    friend std::ostream& operator<< (std::ostream &out, const Matrix &mtx);
};


#endif //MATRIX_MULTIPLICATION_THREADING_MATRIX_H
