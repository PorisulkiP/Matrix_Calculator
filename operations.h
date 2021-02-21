#ifndef OPERATIONS_H
#define OPERATIONS_H

int init();

void consolOut(double **first_matrix, double **second_matrix, double **ansArr, int row, int col);

void matrixGenerator(double **arr, const int row, const int col);

void consolInputMatrix(double **arr, int row, int col);

void consolPrintMatrix(double **arr, int row, int col);

//void switchAB(double **firstArr, double **secondArr,
//              double **ansArr, const int row, const int col);

void summMatrixes(double **firstArr, double **secondArr, double **ansArr, int row, int col);

void subtractMatrixes(double **firstArr, double **secondArr, double **ansArr, int row, int col);

void addMatrixes(double **firstArr, double **secondArr, double **ansArr, int row, int col);

void addNumToMatrix(double **firstArr, int num, double **ansArr, int row, int col);

int inverseMatrix(double **arr, int **inverseArr, int row, int col);

void exponentiationMatrix(double **firstArr, int num, double **ansArr, int row, int col);

double determinate(double **firstArr, int row, int col, int m);

void delDynamicArray(double **firstArr, const int row, const int col);

#endif
