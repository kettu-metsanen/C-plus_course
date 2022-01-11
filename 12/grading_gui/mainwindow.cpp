#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <gradecounter.hh>
#include <iostream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countPushButton_clicked()
{
    /*int E = 0;
    int P = 0;
    int G = 0;
    int N = 0;
    //int result = 0;
    ui->spinBoxE->valueChanged(E);
    ui->spinBoxP->valueChanged(P);
    ui->spinBoxG->valueChanged(G);
    ui->spinBoxN->valueChanged(N);

    std::cout << N << std::endl;
    std::cout << G << std::endl;
    std::cout << P << std::endl;
    std::cout << E << std::endl;*/

    int result = count_final_grade(ui->spinBoxN->value(),ui->spinBoxG->value(),ui->spinBoxP->value(),ui->spinBoxE->value());
    //std::cout << result << std::endl;
    ui->textBrowser->setPlainText("Total grade: " + QString::number(result));

}

