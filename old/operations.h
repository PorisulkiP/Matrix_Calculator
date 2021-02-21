#ifndef OPERATIONS_H
#define OPERATIONS_H

void matrixGenerator(double arr[], int row, int col);

void inputMatrix(double arr[][3], int row, int col);

void printMatrix(double arr[][3], int row, int col);

void summMatrixes(double firstArr[][3], double secondArr[][3], double ansArr[][3], int row, int col);

void subtractMatrixes(double firstArr[][3], double secondArr[][3], double ansArr[][3], int row, int col);

void addMatrixes(double firstArr[][3], double secondArr[][3], double ansArr[][3], int row, int col);

void addNumToMatrix(double firstArr[][3], int num, double ansArr[][3], int row, int col);

int inverseMatrix(double arr[][3], int inverseArr[][3], int row, int col);

void divideMatrixes(double firstArr[][3], double secondArr[][3], double ansArr[][3], double intermediateArr[][3], int row, int col);

void exponentiationMatrix(double firstArr[][3], int num, double ansArr[][3], int row, int col);

#endif