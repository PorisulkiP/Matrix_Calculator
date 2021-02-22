#include <string>
#include <iostream>
#include <ctime>
#include <QMessageBox>
#include <QString>

#include "mainwindow.h"
#include "operations.h"
#include "./ui_mainwindow.h"

int operatorFlag = 1;

//конструктор
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);//при запуске файла
    on_plus_clicked(true);

    // Задаём первичные значения матриц
    ui->sizeA_val_row->setCurrentIndex(1);
    ui->sizeA_val_col->setCurrentIndex(1);
    ui->sizeB_val_raw->setCurrentIndex(1);
    ui->sizeB_val_col->setCurrentIndex(1);

    ui->A8->setText("1");    ui->A6->setText("1");
    ui->A7->setText("1");    ui->A4->setText("1");
    ui->A5->setText("1");    ui->A3->setText("1");
    ui->A2->setText("1");    ui->A1->setText("1");
    ui->A0->setText("1");

    ui->B8->setText("2");    ui->B6->setText("2");
    ui->B7->setText("2");    ui->B4->setText("2");
    ui->B5->setText("2");    ui->B3->setText("2");
    ui->B2->setText("2");    ui->B1->setText("2");
    ui->B0->setText("2");

}

//деструктор
MainWindow::~MainWindow() //при закрытии файла
{
    delete ui;
}

void MainWindow::init(int calling_code)
{
    int row = ui->sizeA_val_col->currentText().toInt();
    int col = ui->sizeA_val_row->currentText().toInt();

    int rowB = ui->sizeB_val_raw->currentText().toInt();
    int colB = ui->sizeB_val_col->currentText().toInt();


    //Создаём двумерные массивы
    double **first_matrix = new double* [row];
    for (int i = 0; i < row; i++)
    {
        first_matrix[i] = new double[col];
    }

    double **second_matrix = new double* [rowB];
    for (int i = 0; i < rowB; i++)
    {
        second_matrix[i] = new double[colB];
    }

    double **ansArr = new double* [row];
    for (int i = 0; i < row; i++)
    {
        ansArr[i] = new double[col];
    }

    arrFill(first_matrix, second_matrix, ansArr, row, col);
    switch (calling_code) {
    case 5: deterA(first_matrix, 1);break;
    case 6: addA(first_matrix, 1);break;
    case 7: expA(first_matrix, 1);break;
    case 8: invertA(first_matrix, 1);break;

    case 9: deterA(second_matrix, 2);break;
    case 10: addA(second_matrix, 2);break;
    case 11: expA(second_matrix, 2);break;
    case 12: invertA(second_matrix, 2);break;

    case 13: deterA(ansArr, 3);break;
    case 14: addA(ansArr, 3);break;
    case 15: expA(ansArr, 3);break;
    case 16: invertA(ansArr, 3);break;

    }
    ansverOut(first_matrix, second_matrix, ansArr, row, col, calling_code);
}

//Заполнение массива по указателям
void MainWindow::arrFill(double **first_matrix,
                            double **second_matrix,
                            double **ansArr,
                            const int row, const int col)
{
    // Заполнение Массивов для вычисления
    int rowA = ui->sizeA_val_row->currentText().toInt();
    int colA = ui->sizeA_val_col->currentText().toInt();

    //Матрица А
    if (rowA == 2 && colA == 2){
        first_matrix[0][0] = ui->A0->text().toInt();        first_matrix[0][1] = ui->A1->text().toInt();
        first_matrix[1][0] = ui->A2->text().toInt();        first_matrix[1][1] = ui->A3->text().toInt();
    }
    else if (rowA == 3 && colA == 3){
        first_matrix[0][0] = ui->A0->text().toInt();        first_matrix[0][1] = ui->A1->text().toInt();        first_matrix[0][2] = ui->A2->text().toInt();
        first_matrix[1][0] = ui->A3->text().toInt();        first_matrix[1][1] = ui->A4->text().toInt();        first_matrix[1][2] = ui->A5->text().toInt();
        first_matrix[2][0] = ui->A6->text().toInt();        first_matrix[2][1] = ui->A7->text().toInt();        first_matrix[2][2] = ui->A8->text().toInt();
    }
    else if (rowA == 3 && colA == 2){
        first_matrix[0][0] = ui->A0->text().toInt();        first_matrix[0][1] = ui->A1->text().toInt();
        first_matrix[1][0] = ui->A2->text().toInt();        first_matrix[1][1] = ui->A3->text().toInt();
        first_matrix[2][0] = ui->A4->text().toInt();        first_matrix[2][1] = ui->A5->text().toInt();
    }
    else if (rowA == 2 && colA == 3){
        first_matrix[0][0] = ui->A0->text().toInt();        first_matrix[0][1] = ui->A1->text().toInt();        first_matrix[0][2] = ui->A2->text().toInt();
        first_matrix[1][0] = ui->A3->text().toInt();        first_matrix[1][1] = ui->A4->text().toInt();        first_matrix[1][2] = ui->A5->text().toInt();
    }

    //Матрица В
    if (rowA == 2 && colA == 2){
        second_matrix[0][0] = ui->B0->text().toInt();        second_matrix[0][1] = ui->B1->text().toInt();
        second_matrix[1][0] = ui->B2->text().toInt();        second_matrix[1][1] = ui->B3->text().toInt();
    }
    else if (rowA == 3 && colA == 3){
        second_matrix[0][0] = ui->B0->text().toInt();        second_matrix[0][1] = ui->B1->text().toInt();        second_matrix[0][2] = ui->B2->text().toInt();
        second_matrix[1][0] = ui->B3->text().toInt();        second_matrix[1][1] = ui->B4->text().toInt();        second_matrix[1][2] = ui->B5->text().toInt();
        second_matrix[2][0] = ui->B6->text().toInt();        second_matrix[2][1] = ui->B7->text().toInt();        second_matrix[2][2] = ui->B8->text().toInt();
    }
    else if (rowA == 3 && colA == 2){
        second_matrix[0][0] = ui->B0->text().toInt();        second_matrix[0][1] = ui->B1->text().toInt();
        second_matrix[1][0] = ui->B2->text().toInt();        second_matrix[1][1] = ui->B3->text().toInt();
        second_matrix[2][0] = ui->B4->text().toInt();        second_matrix[2][1] = ui->B5->text().toInt();
    }
    else if (rowA == 2 && colA == 3){
        second_matrix[0][0] = ui->B0->text().toInt();        second_matrix[0][1] = ui->B1->text().toInt();        second_matrix[0][2] = ui->B2->text().toInt();
        second_matrix[1][0] = ui->B3->text().toInt();        second_matrix[1][1] = ui->B4->text().toInt();        second_matrix[1][2] = ui->B5->text().toInt();
    }
}


// Размер матрицы А
void MainWindow::on_sizeA_val_row_activated(const QString &arg1)
{
    QLayoutItem *ch;

    for (int i = 0; i < ui->matrixA_val->count(); i++) { //Скрываем все элементы
        ch = ui->matrixA_val->itemAt(i);
        ch->widget()->hide();
    }
    on_sizeA_val_col_activated(0);
}

void MainWindow::on_sizeA_val_col_activated(const QString &arg1)
{
    //
    int rowA = ui->sizeA_val_row->currentText().toInt();
    int colA = ui->sizeA_val_col->currentText().toInt();
    QLayoutItem *ch;

    for (int i = 0; i < ui->matrixA_val->count(); i++) { //Скрываем все элементы
        ch = ui->matrixA_val->itemAt(i);
        ch->widget()->hide();
    }

    if (rowA == 2 && colA == 2){
        ui->A0->show();
        ui->A1->show();
        ui->A3->show();
        ui->A4->show();
    }
    else if (rowA == 3 && colA == 3){
        for (int i = 0; i < ui->matrixA_val->count(); i++) { //Показываем все элементы
            ch = ui->matrixA_val->itemAt(i);
            ch->widget()->show();
        }
    }
    else if (rowA == 1 && colA == 1){
        ui->A0->show();
    }
    else if (rowA == 1 && colA == 2){
        ui->A0->show();
        ui->A1->show();
    }
    else if (rowA == 1 && colA == 3){
        ui->A0->show();
        ui->A1->show();
        ui->A2->show();
    }
    else if (rowA == 1 && colA == 1){
        ui->A0->show();
    }
    else if (rowA == 2 && colA == 1){
        ui->A0->show();
        ui->A1->show();
    }
    else if (rowA == 3 && colA == 1){
        ui->A0->show();
        ui->A1->show();
        ui->A2->show();
    }
    else if (rowA == 3 && colA == 2){
        ui->A0->show();
        ui->A1->show();
        ui->A3->show();
        ui->A4->show();
        ui->A6->show();
        ui->A7->show();
    }
    else if (rowA == 2 && colA == 3){
        ui->A0->show();
        ui->A1->show();
        ui->A2->show();
        ui->A3->show();
        ui->A4->show();
        ui->A5->show();
    }
}

// Размер матрицы В
void MainWindow::on_sizeB_val_raw_activated(const QString &arg1)
{
    QLayoutItem *ch;

    for (int i = 0; i < ui->matrixB_val->count(); i++) { //Скрываем все элементы
        ch = ui->matrixB_val->itemAt(i);
        ch->widget()->hide();
    }
    on_sizeB_val_col_activated(0);
}

void MainWindow::on_sizeB_val_col_activated(int index)
{
    int rowB = ui->sizeB_val_raw->currentText().toInt();
    int colB = ui->sizeB_val_col->currentText().toInt();
    QLayoutItem *ch;

    for (int i = 0; i < ui->matrixB_val->count(); i++) { //Скрываем все элементы
        ch = ui->matrixB_val->itemAt(i);
        ch->widget()->hide();
    }

    if (rowB == 2 && colB == 2){
        ui->B0->show();        ui->B1->show();
        ui->B3->show();        ui->B4->show();
    }
    else if (rowB == 3 && colB == 3){
        for (int i = 0; i < ui->matrixB_val->count(); i++) { //Показываем все элементы
            ch = ui->matrixB_val->itemAt(i);
            ch->widget()->show();
        }
    }
    else if (rowB == 1 && colB == 1){
        ui->B0->show();
    }
    else if (rowB == 1 && colB == 2){
        ui->B0->show();        ui->B1->show();
    }
    else if (rowB == 1 && colB == 3){
        ui->B0->show();        ui->B1->show();        ui->B2->show();
    }
    else if (rowB == 2 && colB == 1){
        ui->B0->show();        ui->B3->show();
    }
    else if (rowB == 3 && colB == 1){
        ui->B0->show();        ui->B1->show();        ui->B2->show();
    }
    else if (rowB == 3 && colB == 2){
        ui->B0->show();        ui->B1->show();
        ui->B3->show();        ui->B4->show();
        ui->B6->show();        ui->B7->show();
    }
    else if (rowB == 2 && colB == 3){
        ui->B0->show();        ui->B1->show();        ui->B2->show();
        ui->B3->show();        ui->B4->show();        ui->B5->show();
    }
}

void ans(double **ansArr){

}


void MainWindow::on_equal_bottom_clicked() // При нажатии на равно
{
    init(operatorFlag);
}

void MainWindow::on_plus_clicked(bool checked)
{
    // Выбор сложения
    ui->plus->setStyleSheet("QPushButton{\n"
                            " 	background-color: rgb(148, 148, 148);\n"
                            "	border: none;\n"
                            "}");
    ui->add->setStyleSheet("	background-color: rgb(57, 57, 57);\n"
                           "	border: none;\n"
                           "	color: rgb(228, 228, 228);\n");
    ui->subt->setStyleSheet("	background-color: rgb(57, 57, 57);\n"
                            "	border: none;\n"
                            "	color: rgb(228, 228, 228);\n");
    operatorFlag = 1;
}

void MainWindow::on_add_clicked(bool checked)
{
    //Выбор умножения
    ui->add->setStyleSheet("QPushButton{\n"
                         " 	background-color: rgb(148, 148, 148);\n"
                         "	border: none;\n"
                         "}");
    ui->plus->setStyleSheet("	background-color: rgb(57, 57, 57);\n"
                            "	border: none;\n"
                            "	color: rgb(228, 228, 228);\n");
    ui->subt->setStyleSheet("	background-color: rgb(57, 57, 57);\n"
                            "	border: none;\n"
                            "	color: rgb(228, 228, 228);\n");
    operatorFlag = 3;
}

void MainWindow::on_subt_clicked(bool checked)
{
    // Выбор вычитания
    ui->subt->setStyleSheet("QPushButton{\n"
                           " 	background-color: rgb(148, 148, 148);\n"
                           "	border: none;\n"
                           "}");
    ui->plus->setStyleSheet("	background-color: rgb(57, 57, 57);\n"
                            "	border: none;\n"
                            "	color: rgb(228, 228, 228);\n");
    ui->add->setStyleSheet("	background-color: rgb(57, 57, 57);\n"
                            "	border: none;\n"
                            "	color: rgb(228, 228, 228);\n");
    operatorFlag = 2;
}

void MainWindow::on_switchM_clicked()
{
    //Смена матриц местами
   init(4);
}

void MainWindow::switchM(double **first_matrix,
                         double **second_matrix,
                         double **ansArr,
                         const int row, const int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++) {
            ansArr[i][j] = first_matrix[i][j];

        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++) {
            first_matrix[i][j] = second_matrix[i][j];

        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++) {
            second_matrix[i][j] = ansArr[i][j];

        }
    }

    //Присваивание при смене матриц
    int rowB = ui->sizeB_val_raw->currentText().toInt();
    int colB = ui->sizeB_val_col->currentText().toInt();

    if (rowB == 2 && colB == 2){
        ui->B0->setText(QString::number(second_matrix[0][0]));
        ui->B1->setText(QString::number(second_matrix[0][1]));

        ui->B3->setText(QString::number(second_matrix[1][0]));
        ui->B4->setText(QString::number(second_matrix[1][1]));
    }
    else if (rowB == 3 && colB == 3){
        ui->B0->setText(QString::number(second_matrix[0][0]));
        ui->B0->setText(QString::number(second_matrix[0][1]));
        ui->B1->setText(QString::number(second_matrix[0][1]));
        ui->B2->setText(QString::number(second_matrix[0][2]));

        ui->B3->setText(QString::number(second_matrix[1][0]));
        ui->B4->setText(QString::number(second_matrix[1][1]));
        ui->B5->setText(QString::number(second_matrix[1][2]));

        ui->B6->setText(QString::number(second_matrix[2][0]));
        ui->B7->setText(QString::number(second_matrix[2][1]));
        ui->B8->setText(QString::number(second_matrix[2][2]));
    }
    else if (rowB == 1 && colB == 1){
        ui->B0->setText(QString::number(second_matrix[0][0]));
    }
    else if (rowB == 1 && colB == 2){
        ui->B0->setText(QString::number(second_matrix[0][0]));
        ui->B1->setText(QString::number(second_matrix[0][1]));
    }
    else if (rowB == 1 && colB == 3){
        ui->B0->setText(QString::number(second_matrix[0][0]));
        ui->B1->setText(QString::number(second_matrix[0][1]));
        ui->B2->setText(QString::number(second_matrix[0][2]));
    }
    else if (rowB == 2 && colB == 1){
        ui->B0->setText(QString::number(second_matrix[0][0]));
        ui->B3->setText(QString::number(second_matrix[1][0]));
    }
    else if (rowB == 3 && colB == 1){
        ui->B0->setText(QString::number(second_matrix[0][0]));
        ui->B1->setText(QString::number(second_matrix[0][1]));
        ui->B2->setText(QString::number(second_matrix[1][0]));
    }
    else if (rowB == 3 && colB == 2){
        ui->B0->setText(QString::number(second_matrix[0][0]));
        ui->B1->setText(QString::number(second_matrix[0][1]));

        ui->B3->setText(QString::number(second_matrix[1][0]));
        ui->B4->setText(QString::number(second_matrix[1][1]));

        ui->B6->setText(QString::number(second_matrix[2][0]));
        ui->B7->setText(QString::number(second_matrix[2][1]));
    }
    else if (rowB == 2 && colB == 3){
        ui->B0->setText(QString::number(second_matrix[0][0]));
        ui->B1->setText(QString::number(second_matrix[0][1]));
        ui->B2->setText(QString::number(second_matrix[0][2]));

        ui->B3->setText(QString::number(second_matrix[1][0]));
        ui->B4->setText(QString::number(second_matrix[1][1]));
        ui->B5->setText(QString::number(second_matrix[1][2]));
    }

    // A
    int rowA = ui->sizeA_val_row->currentText().toInt();
    int colA = ui->sizeA_val_col->currentText().toInt();

    if (rowA == 2 && colA == 2){
        ui->A0->setText(QString::number(first_matrix[0][0]));
        ui->A1->setText(QString::number(first_matrix[0][1]));

        ui->A3->setText(QString::number(first_matrix[1][0]));
        ui->A4->setText(QString::number(first_matrix[1][1]));
    }
    else if (rowA == 3 && colA == 3){
        std::cout << "FinalA" << std::endl;
        ui->A0->setText(QString::number(first_matrix[0][0]));
        ui->A1->setText(QString::number(first_matrix[0][1]));
        ui->A2->setText(QString::number(first_matrix[0][2]));

        ui->A3->setText(QString::number(first_matrix[1][0]));
        ui->A4->setText(QString::number(first_matrix[1][1]));
        ui->A5->setText(QString::number(first_matrix[1][2]));

        ui->A6->setText(QString::number(first_matrix[2][0]));
        ui->A7->setText(QString::number(first_matrix[2][1]));
        ui->A8->setText(QString::number(first_matrix[2][2]));
    }
    else if (rowA == 1 && colA == 1){
        ui->A0->setText(QString::number(first_matrix[0][0]));
    }
    else if (rowA == 1 && colA == 2){
        ui->A0->setText(QString::number(first_matrix[0][0]));
        ui->A1->setText(QString::number(first_matrix[0][1]));
    }
    else if (rowA == 1 && colA == 3){
        ui->A0->setText(QString::number(first_matrix[0][0]));
        ui->A1->setText(QString::number(first_matrix[0][1]));
        ui->A2->setText(QString::number(first_matrix[0][2]));
    }
    else if (rowA == 2 && colA == 1){
        ui->A0->setText(QString::number(first_matrix[0][0]));
        ui->A3->setText(QString::number(first_matrix[1][0]));
    }
    else if (rowA == 3 && colA == 1){
        ui->A0->setText(QString::number(first_matrix[0][0]));
        ui->A1->setText(QString::number(first_matrix[0][1]));
        ui->A2->setText(QString::number(first_matrix[1][0]));
    }
    else if (rowA == 3 && colA == 2){
        ui->A0->setText(QString::number(first_matrix[0][0]));
        ui->A1->setText(QString::number(first_matrix[0][1]));

        ui->A3->setText(QString::number(first_matrix[1][0]));
        ui->A4->setText(QString::number(first_matrix[1][1]));

        ui->A6->setText(QString::number(first_matrix[2][0]));
        ui->A7->setText(QString::number(first_matrix[2][1]));
    }
    else if (rowA == 2 && colA == 3){
        ui->A0->setText(QString::number(first_matrix[0][0]));
        ui->A1->setText(QString::number(first_matrix[0][1]));
        ui->A2->setText(QString::number(first_matrix[0][2]));

        ui->A3->setText(QString::number(first_matrix[1][0]));
        ui->A4->setText(QString::number(first_matrix[1][1]));
        ui->A5->setText(QString::number(first_matrix[1][2]));
    }
}

void MainWindow::clean(int matrixNum){
    switch (matrixNum) {
    case 1: {
        ui->A0->setText("");
        ui->A1->setText("");
        ui->A2->setText("");

        ui->A3->setText("");
        ui->A4->setText("");
        ui->A5->setText("");

        ui->A6->setText("");
        ui->A7->setText("");
        ui->A8->setText("");
    }; break;
    case 2: {
        ui->B0->setText("");
        ui->B1->setText("");
        ui->B2->setText("");

        ui->B3->setText("");
        ui->B4->setText("");
        ui->B5->setText("");

        ui->B6->setText("");
        ui->B7->setText("");
        ui->B8->setText("");
    }; break;
    default: ;

    }
}


void MainWindow::on_clean_clicked()
{
    clean(1);
}

void MainWindow::on_cleanB_clicked()
{
    clean(2);
}

void MainWindow::setDeterminate(int det, int matrixNum){
    switch (matrixNum) {
    case 1: {
        ui->determinantA_val->setText(QString::number(det));
    }; break;
    case 2: {
        ui->determinantB_val->setText(QString::number(det));
    }; break;
    case 3: {
        ui->determinantAns_val->setText(QString::number(det));
    }; break;
    default: error(4);

    }

}

void MainWindow::ansverOut(double **firstArr, double **secondArr,
                           double **ansArr, const int row, const int col, int calling_code)
{
    bool flag = false;
    switch (calling_code) {
    case 1:{
        flag = true;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++) {
                ansArr[i][j] = firstArr[i][j] + secondArr[i][j];

            }
        }} ; break;
    case 2:{
        flag = true;for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++) {
                ansArr[i][j] = firstArr[i][j] - secondArr[i][j];

            }
        }} ; break;
    case 3:{
        flag = true;
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
    } ; break;
    case 4: switchM(firstArr, secondArr, ansArr, row, col); break;

    }
    if (flag){
        if (row == 2 && col == 2){
            ui->ans0->setText(QString::number(ansArr[0][0]));
            ui->ans1->setText(QString::number(ansArr[0][1]));

            ui->ans3->setText(QString::number(ansArr[1][0]));
            ui->ans4->setText(QString::number(ansArr[1][1]));
        }
        else if (row == 3 && col == 3){
            std::cout << "FinalA" << std::endl;
            ui->ans0->setText(QString::number(ansArr[0][0]));
            ui->ans1->setText(QString::number(ansArr[0][1]));
            ui->ans2->setText(QString::number(ansArr[0][2]));

            ui->ans3->setText(QString::number(ansArr[1][0]));
            ui->ans4->setText(QString::number(ansArr[1][1]));
            ui->ans5->setText(QString::number(ansArr[1][2]));

            ui->ans6->setText(QString::number(ansArr[2][0]));
            ui->ans7->setText(QString::number(ansArr[2][1]));
            ui->ans8->setText(QString::number(ansArr[2][2]));
        }
        else if (row == 1 && col == 1){
            ui->ans0->setText(QString::number(ansArr[0][0]));
        }
        else if (row == 1 && col == 2){
            ui->ans0->setText(QString::number(ansArr[0][0]));
            ui->ans1->setText(QString::number(ansArr[0][1]));
        }
        else if (row == 1 && col == 3){
            ui->ans0->setText(QString::number(ansArr[0][0]));
            ui->ans1->setText(QString::number(ansArr[0][1]));
            ui->ans2->setText(QString::number(ansArr[0][2]));
        }
        else if (row == 2 && col == 1){
            ui->ans0->setText(QString::number(ansArr[0][0]));
            ui->ans3->setText(QString::number(ansArr[1][0]));
        }
        else if (row == 3 && col == 1){
            ui->ans0->setText(QString::number(ansArr[0][0]));
            ui->ans1->setText(QString::number(ansArr[0][1]));
            ui->ans2->setText(QString::number(ansArr[1][0]));
        }
        else if (row == 3 && col == 2){
            ui->ans0->setText(QString::number(ansArr[0][0]));
            ui->ans1->setText(QString::number(ansArr[0][1]));

            ui->ans3->setText(QString::number(ansArr[1][0]));
            ui->ans4->setText(QString::number(ansArr[1][1]));

            ui->ans6->setText(QString::number(ansArr[2][0]));
            ui->ans7->setText(QString::number(ansArr[2][1]));
        }
        else if (row == 2 && col == 3){
            ui->ans0->setText(QString::number(ansArr[0][0]));
            ui->ans1->setText(QString::number(ansArr[0][1]));
            ui->ans2->setText(QString::number(ansArr[0][2]));

            ui->ans3->setText(QString::number(ansArr[1][0]));
            ui->ans4->setText(QString::number(ansArr[1][1]));
            ui->ans5->setText(QString::number(ansArr[1][2]));
        }
    }
}

void MainWindow::error(int code){
    QMessageBox messageBox;
    switch (code) {
    case 1: ; break;
    case 2: ; break;
    case 3: ; break;
    case 4: messageBox.critical(0,"Ошибка","Невозможно вычислить определитель!"); break;
    }

    messageBox.setFixedSize(500,200);
}

void MainWindow::deterA(double **firstArr, int matrixNum){

    std::srand(time_t(NULL));
    switch (matrixNum) {
    case 1: {
        ui->determinantA_val->setText(QString::number(rand() % 10));
    }; break;
    case 2: {
        ui->determinantB_val->setText(QString::number(rand() % 200));
    }; break;
    case 3: {
        ui->determinantAns_val->setText(QString::number(rand() % 1000));
    }; break;
    default: error(4);
    }
}

void MainWindow::addA(double **firstArr, int matrixNum){
    int rowA = ui->sizeA_val_row->currentText().toInt();
    int colA = ui->sizeA_val_col->currentText().toInt();
    int a = ui->add_val->text().toInt();

    for (int i = 0; i < rowA; i++)
    {
        for (int j = 0; j < colA; j++) {
            firstArr[i][j] = firstArr[i][j] * a;
        }
    }

    switch (matrixNum) {
    case 2: {
        if (rowA == 2 && colA == 2){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));
        }
        else if (rowA == 3 && colA == 3){
            std::cout << "FinalA" << std::endl;
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[0][2]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));
            ui->B5->setText(QString::number(firstArr[1][2]));

            ui->B6->setText(QString::number(firstArr[2][0]));
            ui->B7->setText(QString::number(firstArr[2][1]));
            ui->B8->setText(QString::number(firstArr[2][2]));
        }
        else if (rowA == 1 && colA == 1){
            ui->B0->setText(QString::number(firstArr[0][0]));
        }
        else if (rowA == 1 && colA == 2){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
        }
        else if (rowA == 1 && colA == 3){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[0][2]));
        }
        else if (rowA == 2 && colA == 1){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B3->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 1){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 2){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));

            ui->B6->setText(QString::number(firstArr[2][0]));
            ui->B7->setText(QString::number(firstArr[2][1]));
        }
        else if (rowA == 2 && colA == 3){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[0][2]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));
            ui->B5->setText(QString::number(firstArr[1][2]));
        }}; break;
    case 1:{if (rowA == 2 && colA == 2){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));
        }
        else if (rowA == 3 && colA == 3){
            std::cout << "FinalA" << std::endl;
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[0][2]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));
            ui->A5->setText(QString::number(firstArr[1][2]));

            ui->A6->setText(QString::number(firstArr[2][0]));
            ui->A7->setText(QString::number(firstArr[2][1]));
            ui->A8->setText(QString::number(firstArr[2][2]));
        }
        else if (rowA == 1 && colA == 1){
            ui->A0->setText(QString::number(firstArr[0][0]));
        }
        else if (rowA == 1 && colA == 2){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
        }
        else if (rowA == 1 && colA == 3){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[0][2]));
        }
        else if (rowA == 2 && colA == 1){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A3->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 1){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 2){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));

            ui->A6->setText(QString::number(firstArr[2][0]));
            ui->A7->setText(QString::number(firstArr[2][1]));
        }
        else if (rowA == 2 && colA == 3){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[0][2]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));
            ui->A5->setText(QString::number(firstArr[1][2]));
        }} ; break;
    case 3: {
        if (rowA == 2 && colA == 2){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));
        }
        else if (rowA == 3 && colA == 3){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[0][2]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));
            ui->ans5->setText(QString::number(firstArr[1][2]));

            ui->ans6->setText(QString::number(firstArr[2][0]));
            ui->ans7->setText(QString::number(firstArr[2][1]));
            ui->ans8->setText(QString::number(firstArr[2][2]));
        }
        else if (rowA == 1 && colA == 1){
            ui->ans0->setText(QString::number(firstArr[0][0]));
        }
        else if (rowA == 1 && colA == 2){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
        }
        else if (rowA == 1 && colA == 3){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[0][2]));
        }
        else if (rowA == 2 && colA == 1){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans3->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 1){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 2){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));

            ui->ans6->setText(QString::number(firstArr[2][0]));
            ui->ans7->setText(QString::number(firstArr[2][1]));
        }
        else if (rowA == 2 && colA == 3){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[0][2]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));
            ui->ans5->setText(QString::number(firstArr[1][2]));
        }

    }; break;
    }
}

void MainWindow::expA(double **firstArr, int matrixNum){
    int rowA = ui->sizeA_val_row->currentText().toInt();
    int colA = ui->sizeA_val_col->currentText().toInt();
    int a = ui->exp_val->text().toInt();
    int n;

    for (int i = 0; i < rowA; i++)
    {
        for (int j = 0; j < colA; j++) {
            for (int z = 0; z < a; z++) {
               n = firstArr[i][j] * firstArr[i][j];
            }
            firstArr[i][j] = n;
        }
    }

    switch (matrixNum) {
    case 2: {
        if (rowA == 2 && colA == 2){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));
        }
        else if (rowA == 3 && colA == 3){
            std::cout << "FinalA" << std::endl;
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[0][2]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));
            ui->B5->setText(QString::number(firstArr[1][2]));

            ui->B6->setText(QString::number(firstArr[2][0]));
            ui->B7->setText(QString::number(firstArr[2][1]));
            ui->B8->setText(QString::number(firstArr[2][2]));
        }
        else if (rowA == 1 && colA == 1){
            ui->B0->setText(QString::number(firstArr[0][0]));
        }
        else if (rowA == 1 && colA == 2){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
        }
        else if (rowA == 1 && colA == 3){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[0][2]));
        }
        else if (rowA == 2 && colA == 1){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B3->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 1){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 2){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));

            ui->B6->setText(QString::number(firstArr[2][0]));
            ui->B7->setText(QString::number(firstArr[2][1]));
        }
        else if (rowA == 2 && colA == 3){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[0][2]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));
            ui->B5->setText(QString::number(firstArr[1][2]));
        }}; break;
    case 1:{if (rowA == 2 && colA == 2){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));
        }
        else if (rowA == 3 && colA == 3){
            std::cout << "FinalA" << std::endl;
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[0][2]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));
            ui->A5->setText(QString::number(firstArr[1][2]));

            ui->A6->setText(QString::number(firstArr[2][0]));
            ui->A7->setText(QString::number(firstArr[2][1]));
            ui->A8->setText(QString::number(firstArr[2][2]));
        }
        else if (rowA == 1 && colA == 1){
            ui->A0->setText(QString::number(firstArr[0][0]));
        }
        else if (rowA == 1 && colA == 2){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
        }
        else if (rowA == 1 && colA == 3){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[0][2]));
        }
        else if (rowA == 2 && colA == 1){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A3->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 1){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 2){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));

            ui->A6->setText(QString::number(firstArr[2][0]));
            ui->A7->setText(QString::number(firstArr[2][1]));
        }
        else if (rowA == 2 && colA == 3){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[0][2]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));
            ui->A5->setText(QString::number(firstArr[1][2]));
        }} ; break;
    case 3: {
        if (rowA == 2 && colA == 2){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));
        }
        else if (rowA == 3 && colA == 3){
            std::cout << "FinalA" << std::endl;
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[0][2]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));
            ui->ans5->setText(QString::number(firstArr[1][2]));

            ui->ans6->setText(QString::number(firstArr[2][0]));
            ui->ans7->setText(QString::number(firstArr[2][1]));
            ui->ans8->setText(QString::number(firstArr[2][2]));
        }
        else if (rowA == 1 && colA == 1){
            ui->ans0->setText(QString::number(firstArr[0][0]));
        }
        else if (rowA == 1 && colA == 2){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
        }
        else if (rowA == 1 && colA == 3){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[0][2]));
        }
        else if (rowA == 2 && colA == 1){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans3->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 1){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 2){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));

            ui->ans6->setText(QString::number(firstArr[2][0]));
            ui->ans7->setText(QString::number(firstArr[2][1]));
        }
        else if (rowA == 2 && colA == 3){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[0][2]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));
            ui->ans5->setText(QString::number(firstArr[1][2]));
        }

    }; break;
    }
}


void MainWindow::invertA(double **firstArr, int matrixNum){
    int rowA = ui->sizeA_val_row->currentText().toInt();
    int colA = ui->sizeA_val_col->currentText().toInt();

    for (int i = 0; i < rowA; i++)
    {
        for (int j = 0; j < colA; j++) {
            firstArr[i][j] = firstArr[i][j] / 5;
        }
    }
    switch (matrixNum) {
    case 2: {
        if (rowA == 2 && colA == 2){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));
        }
        else if (rowA == 3 && colA == 3){
            std::cout << "FinalA" << std::endl;
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[0][2]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));
            ui->B5->setText(QString::number(firstArr[1][2]));

            ui->B6->setText(QString::number(firstArr[2][0]));
            ui->B7->setText(QString::number(firstArr[2][1]));
            ui->B8->setText(QString::number(firstArr[2][2]));
        }
        else if (rowA == 1 && colA == 1){
            ui->B0->setText(QString::number(firstArr[0][0]));
        }
        else if (rowA == 1 && colA == 2){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
        }
        else if (rowA == 1 && colA == 3){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[0][2]));
        }
        else if (rowA == 2 && colA == 1){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B3->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 1){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 2){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));

            ui->B6->setText(QString::number(firstArr[2][0]));
            ui->B7->setText(QString::number(firstArr[2][1]));
        }
        else if (rowA == 2 && colA == 3){
            ui->B0->setText(QString::number(firstArr[0][0]));
            ui->B1->setText(QString::number(firstArr[0][1]));
            ui->B2->setText(QString::number(firstArr[0][2]));

            ui->B3->setText(QString::number(firstArr[1][0]));
            ui->B4->setText(QString::number(firstArr[1][1]));
            ui->B5->setText(QString::number(firstArr[1][2]));
        }}; break;
    case 1:{if (rowA == 2 && colA == 2){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));
        }
        else if (rowA == 3 && colA == 3){
            std::cout << "FinalA" << std::endl;
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[0][2]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));
            ui->A5->setText(QString::number(firstArr[1][2]));

            ui->A6->setText(QString::number(firstArr[2][0]));
            ui->A7->setText(QString::number(firstArr[2][1]));
            ui->A8->setText(QString::number(firstArr[2][2]));
        }
        else if (rowA == 1 && colA == 1){
            ui->A0->setText(QString::number(firstArr[0][0]));
        }
        else if (rowA == 1 && colA == 2){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
        }
        else if (rowA == 1 && colA == 3){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[0][2]));
        }
        else if (rowA == 2 && colA == 1){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A3->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 1){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 2){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));

            ui->A6->setText(QString::number(firstArr[2][0]));
            ui->A7->setText(QString::number(firstArr[2][1]));
        }
        else if (rowA == 2 && colA == 3){
            ui->A0->setText(QString::number(firstArr[0][0]));
            ui->A1->setText(QString::number(firstArr[0][1]));
            ui->A2->setText(QString::number(firstArr[0][2]));

            ui->A3->setText(QString::number(firstArr[1][0]));
            ui->A4->setText(QString::number(firstArr[1][1]));
            ui->A5->setText(QString::number(firstArr[1][2]));
        }} ; break;
    case 3: {
        if (rowA == 2 && colA == 2){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));
        }
        else if (rowA == 3 && colA == 3){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[0][2]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));
            ui->ans5->setText(QString::number(firstArr[1][2]));

            ui->ans6->setText(QString::number(firstArr[2][0]));
            ui->ans7->setText(QString::number(firstArr[2][1]));
            ui->ans8->setText(QString::number(firstArr[2][2]));
        }
        else if (rowA == 1 && colA == 1){
            ui->ans0->setText(QString::number(firstArr[0][0]));
        }
        else if (rowA == 1 && colA == 2){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
        }
        else if (rowA == 1 && colA == 3){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[0][2]));
        }
        else if (rowA == 2 && colA == 1){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans3->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 1){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[1][0]));
        }
        else if (rowA == 3 && colA == 2){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));

            ui->ans6->setText(QString::number(firstArr[2][0]));
            ui->ans7->setText(QString::number(firstArr[2][1]));
        }
        else if (rowA == 2 && colA == 3){
            ui->ans0->setText(QString::number(firstArr[0][0]));
            ui->ans1->setText(QString::number(firstArr[0][1]));
            ui->ans2->setText(QString::number(firstArr[0][2]));

            ui->ans3->setText(QString::number(firstArr[1][0]));
            ui->ans4->setText(QString::number(firstArr[1][1]));
            ui->ans5->setText(QString::number(firstArr[1][2]));
        }
    }; break;
    }

}

void MainWindow::on_deter_clicked()
{
    init(5);
}

void MainWindow::on_addButton_clicked()
{
    init(6);
}

void MainWindow::on_expButton_clicked()
{
    init(7);
}

void MainWindow::on_invert_clicked()
{
    init(8);
}

void MainWindow::on_deterB_clicked()
{
    init(9);
}

void MainWindow::on_addButtonB_clicked()
{
    init(10);
}

void MainWindow::on_expButtonB_clicked()
{
    init(11);
}

void MainWindow::on_invertB_clicked()
{
    init(12);
}

void MainWindow::on_deterAns_clicked()
{
    init(13);
}

void MainWindow::on_addButtonAns_clicked()
{
    init(14);
}

void MainWindow::on_expButtonAns_clicked()
{
    init(15);
}

void MainWindow::on_invertAns_clicked()
{
    init(16);
}
