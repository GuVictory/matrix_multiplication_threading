cmake_minimum_required(VERSION 3.17)
project(matrix_multiplication_threading)

set(CMAKE_CXX_STANDARD 17)

add_executable(matrix_multiplication_threading main.cpp ./src/Matrix.cpp ./src/ThreadWorker.cpp)

target_include_directories(matrix_multiplication_threading PUBLIC ./include)