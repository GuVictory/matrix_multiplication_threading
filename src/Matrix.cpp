//
// Created by Виктория Губанова on 22.09.2020.
//

#include "Matrix.h"
#include <string>
#include <fstream>
#include <ThreadWorker.h>

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

// Возвращает размерность матрицы
int Matrix::getSize() const {
    return this->matrix.size();
}

// Перегрузка [] для изменения элементов матрицы
std::vector<int> &Matrix::operator[](const int index) {
    return this->matrix[index];
}

// Перегрузка [] для обращения к элементам матрицы
const std::vector<int> &Matrix::operator[](const int index) const {
    return this->matrix[index];
}

Matrix operator*(const Matrix &mtx1, const Matrix &mtx2) {
    try {
        if (mtx1.getSize() != mtx2.getSize()) {
            throw -1;
        }

        const int matrixSize = mtx1.getSize();
        auto* resultMatrix = new Matrix(matrixSize);
        ThreadWorker::multithreadingOperationExecution(Operations::multiplication, *resultMatrix, mtx1, mtx2);

        return *resultMatrix;

    } catch (int err) {
        std::cerr << "Размеры матриц не совпадают!" << std::endl;
    } catch (...) {
        std::cerr << "Общая ошибка" << std::endl;
    }
}

void Matrix::multiplyThreading(int numberOfThreads, int currentThreadNumber, Matrix &result, const Matrix &m1,
                               const Matrix &m2) {

    const int matrixSize = m1.getSize();

    // Количество элементов в матрице
    const int numberOfElements = (matrixSize * matrixSize);

    // Количество операций, которое должен произвести каждый поток
    const int numberOfOperations = numberOfElements / numberOfThreads;

    // Остаточное количесвто операций, которые кто-то должен произвести
    const int restOperations = numberOfElements % numberOfThreads;

    int start_op = 0,  // Включая
    end_op = 0;    // Не включая


    /* Распределение по потокам на примере матрицы 4x4
     * Thread 0:
     *      start_op = 5 * 0 = 0
     *      end_op = 5 * (0 + 1) + 1 = 6;
     * Thread 1:
     *      start_op = 5 * 1 + 1 = 6
     *      end_op = 5 * (1 + 1) + 1 = 11;
     * Thread 2:
     *      start_op = 5 * 2 + 1 = 11
     *      end_op = 5 * (2 + 1) + 1 = 16;
     * */

    if (currentThreadNumber == 0) {
        // Первый поток берет на себя большую часть работы
        start_op = numberOfOperations * currentThreadNumber;
        end_op = (numberOfOperations * (currentThreadNumber + 1)) + restOperations;
    }
    else {
        start_op = numberOfOperations * currentThreadNumber + restOperations;
        end_op = (numberOfOperations * (currentThreadNumber + 1)) + restOperations;
    }

    for (int op = start_op; op < end_op; ++op) {
        // Переводим индекс 1й размерности в 2ю
        const int row = op % matrixSize;
        const int col = op / matrixSize;
        int r = 0;
        for (int i = 0; i < matrixSize; ++i) {
            const int e1 = m1[row][i];
            const int e2 = m2[i][col];
            r += e1 * e2;
        }
        result[row][col] = r;
    }

}
