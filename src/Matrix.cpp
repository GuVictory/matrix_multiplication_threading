//
// Created by Виктория Губанова on 22.09.2020.
//

#include "Matrix.h"
#include <string>
#include <fstream>

Matrix::Matrix() {}

Matrix::Matrix(int size) {
    this->matrix = std::vector<std::vector<int>>(size);
    for (auto row : this->matrix) {
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

