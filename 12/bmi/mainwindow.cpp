#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>

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


void MainWindow::on_countButton_clicked()
{
    QString local_height = ui->heightLineEdit->text();
    QString local_weight = ui->weightLineEdit->text();
    if(local_height == "0" or local_height == "")
    {
        ui->resultLabel->setText("Cannot count");
        return;
    }
    float bmi = local_weight.toInt()/pow(local_height.toFloat()/100,2);
    qDebug() << bmi;
    ui->resultLabel->setText(QString::number(bmi,'g', 6));
    //ui->infoTextBrowser->clear();
    if(bmi < 18.5)
    {
        ui->infoTextBrowser->setText("You are underweight.");
    }
    else if(bmi >= 18.5 && bmi <= 25)
    {
        ui->infoTextBrowser->setText("Your weight is normal.");
    }
    else
    {
        ui->infoTextBrowser->setText("You are overweight.");
    }
}

