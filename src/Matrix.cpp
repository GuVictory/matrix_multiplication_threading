//
// Created by Виктория Губанова on 22.09.2020.
//

#include "Matrix.h"
#include <string>
#include <fstream>

Matrix::Matrix() {}

Matrix::Matrix(int size) {
    this->matrix = std::vector<std::vector<int>>(size);
    for (auto& row : this->matrix) {
        row = std::vector<int>(size);
    }
}

Matrix::Matrix(const std::string& filename) {
    std::ifstream in(filename);

    std::string delim = " ";
    std::string line;

    size_t pos = 0;
    size_t delimSize = delim.size();
    std::string temp;
    char* pEnd;

    if (in.is_open())
    {
        while (getline(in, line)) {
            std::vector<int> elementsOfLine;
            pos = 0;
            while (pos < line.size()) {
                temp = temp.assign(line, pos, line.find(delim, pos) - pos);
                if (!temp.empty()) {
                    elementsOfLine.push_back(strtol(temp.c_str(), &pEnd, 10));
                }
                pos += temp.size() + delimSize;
            }
            this->matrix.push_back(elementsOfLine);
        }
    }
}

Matrix::~Matrix() {
    for (auto row : this->matrix) {
        row.clear();
    }
    this->matrix.clear();
}

std::ostream &operator<<(std::ostream &out, const Matrix &mtx) {
    for (const auto& row : mtx.matrix) {
        for (auto el : row) {
            out << el << " ";
        }
        out << std::endl;
    }
    return out;
}

Matrix::Matrix(const Matrix &mtx) {
    this->matrix = mtx.matrix;
}

Matrix operator*(const Matrix &mtx1, const Matrix &mtx2) {
    try {
        if (mtx1.matrix.size() != mtx2.matrix.size()) {
            throw -1;
        }

        const int matrixSize = mtx1.matrix.size();
        auto* resultMatrix = new Matrix(matrixSize);

        for (int i = 0; i < matrixSize; ++i) {
            for (int j = 0; j < matrixSize; ++j) {
                int result = 0;
                for (int k = 0; k < matrixSize; ++k) {
                    const int e1 = mtx1.matrix[i][k];
                    const int e2 = mtx2.matrix[k][j];
                    result += e1 * e2;
                }
                resultMatrix->matrix[i][j] = result;
            }
        }
        return *resultMatrix;

    } catch (int err) {
        std::cerr << "Размеры матриц не совпадают!" << std::endl;
    } catch (...) {
        std::cerr << "Общая ошибка" << std::endl;
    }
}

