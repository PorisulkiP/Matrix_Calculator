#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init(int calling_code);
    void arrFill(double **first_matrix,
                    double **second_matrix,
                    double **ansArr,
                    const int row, const int col);
    void ans(double **ansArr);
    void switchM(double **first_matrix,
                 double **second_matrix,
                 double **ansArr,
                 const int row, const int col);
    void clean(int matrixNum);
    void setDeterminate(int det, int matrixNum);

    void error(int code);
    void ansverOut(double **firstArr, double **secondArr,
                   double **ansArr, const int row, const int col, int calling_code);
    void deterA(double **firstArr, int matrixNum);
    void addA(double **firstArr, int matrixNum);
    void expA(double **firstArr, int matrixNum);
    void invertA(double **firstArr, int matrixNum);

private slots:
    void on_sizeA_val_row_activated(const QString &arg1);

    void on_sizeA_val_col_activated(const QString &arg1);

    void on_equal_bottom_clicked();

    void on_plus_clicked(bool checked);

    void on_add_clicked(bool checked);

    void on_subt_clicked(bool checked);

    void on_switchM_clicked();

    void on_sizeB_val_raw_activated(const QString &arg1);

    void on_sizeB_val_col_activated(int index);

    void on_clean_clicked();

    void on_cleanB_clicked();

    void on_deter_clicked();

    void on_addButton_clicked();

    void on_expButton_clicked();

    void on_invert_clicked();

    void on_deterB_clicked();

    void on_invertB_clicked();

    void on_deterAns_clicked();

    void on_invertAns_clicked();

    void on_addButtonB_clicked();

    void on_expButtonB_clicked();

    void on_addButtonAns_clicked();

    void on_expButtonAns_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
