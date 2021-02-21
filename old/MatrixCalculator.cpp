#include <string>
#include <iostream>
#include <ctime>
#include "operations.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    int row = 3;
    int col = 3;

    //double ** first_matrix = new double* [row];
    //for (size_t i = 0; i < row; i++)
    //{
    //    first_matrix[i] = new double[col];
    //}

    //double** second_matrix = new double* [row];
    //for (size_t i = 0; i < row; i++)
    //{
    //    second_matrix[i] = new double[col];
    //}

    double first_matrix[3][3]
    { 
       {5, 6, 3}, 
       {2, 3, 6}, 
       {1, 4, 8} 
    };
    double second_matrix[3][3]
    {
       {5, 4, 7},
       {8, 7, 4},
       {9, 6, 2}
    };

    double ansArr[3][3]{};
    double intermediateArr[3][3]{};
    
    int choice, num;
    cout << "Выберите действие: " << endl;
    cout << "1. Сумма двух матриц" << endl;
    cout << "2. Вычитание матрицы из матрицы" << endl;
    cout << "3. Умножение матрицы на матрицу" << endl;
    cout << "4. Умножение матрицы на число" << endl;
    cout << "5. Деление матрицы на матрицу" << endl;    
    cout << "6. Возведение матрицы в степень" << endl;
    cin >> choice;
    string sign  = "+";
    switch (choice)
    {
    case 1: summMatrixes(first_matrix, second_matrix, ansArr, row, col); sign = "+" ; break;
        case 2: subtractMatrixes(first_matrix, second_matrix, ansArr, row, col); sign = "-"; break;
        case 3: addMatrixes(first_matrix, second_matrix, ansArr, row, col); sign = "*"; break;
        case 4: {
            cout << "Введите число для умножения на него матрицы: ";
            cin >> num;
            addNumToMatrix(first_matrix, num, ansArr, row, col); sign = "*"; break;
        }
        case 5: divideMatrixes(first_matrix, second_matrix, ansArr, intermediateArr, row, col); sign = "/"; break;
        case 6: {
            cout << "Введите степень для матрицы: ";
            cin >> num;
            exponentiationMatrix(first_matrix, num, ansArr, row, col); sign = "^"; break; 
            }
        default: printMatrix(first_matrix, row, col); break;
    }
    if (choice != 4 and choice != 6)
    {
       printMatrix(first_matrix, row, col);
       cout << "\t  " << sign << " \n" << endl;
       printMatrix(second_matrix, row, col);
       printMatrix(ansArr, row, col);
    }
    else {
       printMatrix(first_matrix, row, col);
       cout << "\t  " << sign << " \n" << endl;
       cout << "\t  " << num << " \n" << endl;
       printMatrix(ansArr, row, col);
    }
    return 0;
}
