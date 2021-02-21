#include <string>
#include <iostream>
#include <ctime>

void matrixGenerator(double arr[], int row, int col) {
    // Генератор случайно матрицы
    std::srand(time_t(NULL));

    for (int i = 0; i <= 9; i++)
    {
        arr[i] = rand() % 100;
    }

    for (int i = 0; i < 9; i++)
    {
        if (i % row == 0)
            std::cout << arr[i];
        else
            std::cout << std::endl;
    }
}

void inputMatrix(double arr[][3], int row, int col) {
    // ���� ������� � �������
    std::cout << "������� �������: " << std::endl;
    double a;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cin >> a;
            arr[i][j] = a;
        }
    }
}

void printMatrix(double arr[][3], int row, int col) {
    // ����� �������
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

void summMatrixes(double firstArr[][3], double secondArr[][3], double ansArr[][3], int row, int col) {
    // �������� ���� ������
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++) {
            ansArr[i][j] = firstArr[i][j] + secondArr[i][j];
        }
    }
}

void subtractMatrixes(double firstArr[][3], double secondArr[][3], 
                      double ansArr[][3], int row, int col) {
    // ��������� ���� ������
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++) {
            ansArr[i][j] = firstArr[i][j] - secondArr[i][j];
        }
    }
}

void addMatrixes(double firstArr[][3], double secondArr[][3], double ansArr[][3], int row, int col) {
    // ��������� ���� ������
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

void addNumToMatrix(double firstArr[][3], int num, double ansArr[][3], int row, int col) {
    // ��������� ������� �� �����
    int a;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            ansArr[i][j] += firstArr[i][j] * num;
        }
    }
}

void exponentiationMatrix(double firstArr[][3], int num, double ansArr[][3], int row, int col) {
    // ���������� ������� � �������
    for (int i = 0; i < num; i++)
    {
        addMatrixes(firstArr, firstArr, ansArr, row, col);
    }
}

void inverseMatrix(double firstArr[][3], double inverseArr[][3], int row, int col) {
    // ���������� �������� ������� (������� -1)
    double intermediateArr[3][3] = {
        {1,0,0},
        {0,1,0},
        {0,0,1},
    };
    firstArr = inverseArr;
    printMatrix(inverseArr, row, col);
    for (int j = 0; j < col; j++)
    {
        inverseArr[row][j] -= inverseArr[0][j];
        intermediateArr[row][j] -= intermediateArr[0][j];
    }
    printMatrix(inverseArr, row, col);
    printMatrix(intermediateArr, row, col);
    //for (int j = 0; j < col; j++)
    //{
    //    firstArr[1][j] = firstArr[1][j] - firstArr[0][j]*2;
    //    intermediateArr[1][j] = intermediateArr[1][j] - intermediateArr[0][j]*2;
    //}
    //
    //for (int j = 0; j < col; j++)
    //{
    //    if (row >= 1)
    //    {
    //        firstArr[1][j] = firstArr[1][j] / 0.6;
    //        intermediateArr[1][j] = intermediateArr[1][j] - intermediateArr[0][j] * 2;
    //    }
    //}
}

void divideMatrixes(double firstArr[][3], double secondArr[][3], 
                    double ansArr[][3], double intermediateArr[][3], int row, int col) {
    /*                                        ������� ���� ������.
    �� ����� ���� ������� ������ ������. ��� ����� �������������� ��������, ��� �������� ����� ������� �� �������.
    ������� ���������� ���������� ����� ������� �� �������, �������� ������ �������.*/

    inverseMatrix(secondArr, intermediateArr, row, col);
    //addMatrixes(firstArr, intermediateArr, ansArr, row, col);
}