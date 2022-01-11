#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->lcdNumberSec->setPalette(QPalette(QColor(250, 250, 200)));
    ui->lcdNumberSec->setAutoFillBackground(true);
    ui->lcdNumberMin->setPalette(QPalette(QColor(210, 150, 100)));
    ui->lcdNumberMin->setAutoFillBackground(true);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    mins = 0;
    secs = 0;


}
void MainWindow::showTime()
{


    secs++;
    if(secs == 60)
    {
        secs=0;
        mins++;
    }
    ui->lcdNumberSec->display(secs);
    ui->lcdNumberMin->display(mins);

}


MainWindow::~MainWindow()
{

    delete ui;

}

void MainWindow::on_startButton_clicked()
{
    timer->start(1000);
    //showTime();
}


void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}


void MainWindow::on_resetButton_clicked()
{
    mins=0;
    secs=0;
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);

}

