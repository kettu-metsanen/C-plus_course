#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QFile>


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


void MainWindow::on_findPushButton_clicked()
{
    QString fileName = ui->fileLineEdit->text();
    QString findSano = ui->keyLineEdit->text();
    QString allFile;

    if(fileName != "")
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            ui->textBrowser->setText("File not found");
        }
        else
        {
            if(findSano == "")
            {
                ui->textBrowser->setText("File found");
            }
            else
            {
                QTextStream in(&file);
                allFile = in.readAll();
                file.close();
                if(ui->matchCheckBox->isChecked())
                {
                    if(allFile.contains(findSano, Qt::CaseSensitive))
                    {
                        ui->textBrowser->setText("Word found");
                    }
                    else
                    {
                        ui->textBrowser->setText("Word not found");
                    }
                }
                else
                {
                    if(allFile.contains(findSano, Qt::CaseInsensitive))
                    {
                        ui->textBrowser->setText("Word found");
                    }
                    else
                    {
                        ui->textBrowser->setText("Word not found");
                    }
                }

            }
        }
    }
}

