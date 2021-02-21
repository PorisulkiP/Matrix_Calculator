#include <string>
#include <iostream>
#include <ctime>
#include "mainwindow.h"

void matrixGenerator(double **arr, const int row, const int col) {
    // Генератор матриц
    std::srand(time_t(NULL));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            arr[i][j] = rand() % 100;
        }
    }
}

void consolInputMatrix(double **arr, const int row, const int col) {
    // Ввод матриц через консоль
    std::cout << "Введите матрицу: " << std::endl;
    double a;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cin >> a;
            arr[i][j] = a;
        }
    }
}

void consolPrintMatrix(double **arr, const int row, const int col) {
    // Вывод матрицы в консоль
    std::cout << "\t";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
        std::cout << "\t";
    }
    std::cout << std::endl;
}

void summMatrixes(double **firstArr, double **secondArr,
                  double **ansArr, const int row, const int col) {
    // Сложение двух матриц
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++) {
            ansArr[i][j] = firstArr[i][j] + secondArr[i][j];

        }
    }
}

void subtractMatrixes(double **firstArr, double **secondArr,
                      double **ansArr, const int row, const int col) {
    // Вычитание двух матриц
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++) {
            ansArr[i][j] = firstArr[i][j] - secondArr[i][j];
        }
    }
}

void addMatrixes(double **firstArr, double **secondArr,
                 double **ansArr, const int row, const int col) {
    int a;
    for (int i = 0; i < row; i++ ){
        for (int j = 0; j < col; j++) {
            a = 0;
            for (int z = 0; z < row; z++) {
                a += firstArr[i][z] * secondArr[z][j];
            }
            ansArr[i][j] = a;
        }
    }
}

void addNumToMatrix(double **firstArr,const int num,
                    double **ansArr, const int row, const int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            ansArr[i][j] += firstArr[i][j] * num;
        }
    }
}

void exponentiationMatrix(double **firstArr, int num, double **ansArr, const int row, const int col) {
    for (int i = 0; i < num; i++)
    {
        addMatrixes(firstArr, firstArr, ansArr, row, col);
    }
}

void inverseMatrix(double **firstArr, double **inverseArr,
                   const int row, const int col) {
    double intermediateArr[3][3] = {
        {1,0,0},
        {0,1,0},
        {0,0,1},
    };
    firstArr = inverseArr;
    consolPrintMatrix(inverseArr, row, col);
    for (int j = 0; j < col; j++)
    {
        inverseArr[row][j] -= inverseArr[0][j];
        intermediateArr[row][j] -= intermediateArr[0][j];
    }
}

double determinate(double **firstArr, int row, int col, int matrixNum, int m){
    int n, d, k;
    MainWindow val;

    n = --m;
    if (row == 1 && col == 1){
        val.setDeterminate(firstArr[0][0], matrixNum);
    }
    if (row == 2 && col == 2){
        val.setDeterminate(firstArr[0][0] * firstArr[1][1] - firstArr[1][0] * firstArr[0][1], matrixNum);
    }
    if (row == 3 && col == 3){
        for (int i = 0; i < m; i++) {
            d = d + k * firstArr[i][0] * determinate(firstArr, row, col, matrixNum, n);
            k = -k;
        }
        std::cout << d << matrixNum << std::endl;
        val.setDeterminate(d, matrixNum);
    }
    else{
        val.setDeterminate(0, 0);
    }
    return 0;
}


void delDynamicArray(double **firstArr, const int row, const int col){
    for(int i = 0; i < row*col; i++){
        delete firstArr[i];
    }
    delete[] firstArr;
    firstArr = 0;
}
