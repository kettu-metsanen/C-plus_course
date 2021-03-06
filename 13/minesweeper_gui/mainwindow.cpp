#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <gameboard.hh>
#include <square.hh>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QApplication>
#include <QProcess>
//#include <QMouseEvent>
#include <QPixmap>
#include <qextendedbutton.hh>
#include <QTimer>
#include <QApplication>
#include <QMainWindow>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cancelled_at_start = false;
    bool ok = true;
    int seed = QInputDialog::getInt(this, "Set seed", "Please enter seed for random generator",
                                    0, -2147483647, 2147483647, 1, &ok);
    if(ok == false)
    {
        cancelled_at_start = true;
    }
    icflag.addPixmap(QPixmap("flag.png"));
    icdot.addPixmap(QPixmap("dot.jpg"));
    icquestion.addPixmap(QPixmap("question.png"));
    icmine.addPixmap(QPixmap("mine.jpg"));
    ui->seedEdit->setText(QString::number(seed));
    field_size = 6;
    prepare_playground(seed);

}

void MainWindow::prepare_playground(int seed)
{
    gelapsed = new QTimer(this);
    mins=0;
    secs=0;
    gmbd = new GameBoard(field_size);
    field = new QVector<QVector<QExtendedButton*>>;
    gmbd->init(seed);
    int bsize = gmbd->getSize();

    QMainWindow w; // MOVE TO CLASS HH
    qDebug() << w.screen()->size();

    for(int i=0; i<bsize; i++)
        {
            QVector<QExtendedButton*> line;
            for(int j=0; j<bsize; j++)
            {
                Square sqr = gmbd->getSquare(i,j);
                QString capt = "";
                sqr.hasMine() ? capt="+" : capt=".";
                QExtendedButton* btn = new QExtendedButton(this);

                if(sqr.hasMine()) //for debugging purposes
                {
                    btn->setFlat(true);
                }
                //btn->setFlat(true);
                btn->setAccessibleName(QString::number(i) + QString::number(j));
                btn->setCheckable(true);
                btn->setIcon(icdot);

                connect(btn, &QExtendedButton::rightClicked, this, &MainWindow::right_clicked);
                connect(btn, &QExtendedButton::clicked, this, &MainWindow::left_clicked);
                ui->gridLayout->addWidget(btn, i, j);
                line.push_back(btn);
            }
            field->push_back(line);
        }
    connect(gelapsed, &QTimer::timeout, this, &MainWindow::tick_time);
    gelapsed->start(1000);

}

void MainWindow::tick_time()
{
    secs++;
    ui->lcdTimer->display(QString::number(secs));
}

void MainWindow::left_clicked()
{
    QExtendedButton* pressed = qobject_cast<QExtendedButton*>(sender());
    if(!pressed->isChecked())
    {
        return;
    }
    int idx = ui->gridLayout->indexOf(pressed);
    int row = int(idx/gmbd->getSize());
    int column = idx - (row*gmbd->getSize());
    if(gmbd->getSquare(row, column).hasFlag())
    {
        pressed->setChecked(false);
        return;
    }
    pressed->setChecked(true);
    pressed->setEnabled(false);
    pressed->setIcon(QIcon());
    bool notmine = gmbd->openSquare(row, column);
    if(!notmine)
    {
        gelapsed->stop();
        //open all mines
        for(int i=0; i<gmbd->getSize(); i++)
        {
            for(int j=0; j<gmbd->getSize(); j++)
            {
                if(gmbd->getSquare(i,j).hasMine())
                {
                    field->at(i).at(j)->setIcon(icmine);
                    field->at(i).at(j)->setChecked(true);
                }
                else
                {
                    field->at(i).at(j)->setChecked(true);
                    field->at(i).at(j)->setIcon(QIcon());
                }
            }
        }
        // ask user to repeat the game
        QMessageBox gameEnd;
        gameEnd.setText("Game is ended! Do you want to start again?");
        gameEnd.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int answer = gameEnd.exec();
        if(answer == QMessageBox::Ok)
        {
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }
        else
        {
            qApp->quit();
        }

    }
    for(auto i = 0; i<gmbd->getSize(); i++)
    {
        for(auto j=0; j<gmbd->getSize(); j++)
        {
            Square sq = gmbd->getSquare(i,j);
            if(sq.isOpen())
            {
                field->at(i).at(j)->setChecked(true);
                field->at(i).at(j)->setEnabled(false);
                field->at(i).at(j)->setIcon(QIcon());
            }
        }
    }
    check_game_over();
}

void MainWindow::right_clicked()
{
    QExtendedButton* pressed = qobject_cast<QExtendedButton*>(sender());
    int idx = ui->gridLayout->indexOf(pressed);
    int row = int(idx/gmbd->getSize());
    int column = idx - (row*gmbd->getSize());
    Square sq = gmbd->getSquare(row, column);
    if(!pressed->isFlagged() & !pressed->isQuestioned())
    {
        sq.addFlag();
        gmbd->setSquare(sq, row, column);
        pressed->setIcon(icflag);
        pressed->setQuestioned(false);
        pressed->setFlagged(true);
    }
    else if(pressed->isFlagged())
    {
        sq.removeFlag();
        gmbd->setSquare(sq, row, column);
        pressed->setIcon(icquestion);
        pressed->setQuestioned(true);
        pressed->setFlagged(false);
    }
    else if(pressed->isQuestioned())
    {
        sq.removeFlag();
        gmbd->setSquare(sq, row, column);
        pressed->setIcon(icdot);
        pressed->setQuestioned(false);
        pressed->setFlagged(false);
    }
    check_game_over();
}

void MainWindow::check_game_over()
{
    if(gmbd->isGameOver())
    {
        QMessageBox gameEnd;
        gameEnd.setText("You won! Do you want to start again?");
        gameEnd.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        int answer = gameEnd.exec();
        if(answer == QMessageBox::Ok)
        {
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }
        else
        {
            qApp->quit();
        }
    }
}

MainWindow::~MainWindow()
{
    for(int i=0; i<field->size(); i++)
    {
        for(int j=0; j<field->at(i).size(); j++)
        {
            delete field->at(i).at(j);
        }
    }
    delete gmbd;
    delete gelapsed;
    delete field;
    delete ui;
}



void MainWindow::on_resetButton_clicked()
{
    QString newseed = ui->seedEdit->text();
    int numseed = newseed.toInt(); // if there was text, then numseed = 0
    for(int i=0; i<field->size(); i++)
    {
        for(int j=0; j<field->at(i).size(); j++)
        {
            delete field->at(i).at(j);
        }
    }
    delete gmbd;
    delete gelapsed;
    delete field;
    prepare_playground(numseed);
}


void MainWindow::on_isokButton_clicked()
{
    int right_flags = 0;
    int flags_amount = 0;
    for(auto i = 0; i<field->size(); i++)
    {
        for(auto j = 0; j<field->at(i).size(); j++)
        {
            Square sq = gmbd->getSquare(i, j);
            if(field->at(i).at(j)->isFlagged())
            {
                flags_amount++;
            }

            if(field->at(i).at(j)->isFlagged() & sq.hasMine())
            {
                right_flags++;
            }

        }
    }

    if(flags_amount == 0)
    {
        QMessageBox::information(this, "Minesweeper", "You don't have flags on the board!", QMessageBox::Ok);
    }
    else
    {
        QString to_show = QString::number(right_flags) + " flags out of " + QString::number(flags_amount) + " show correctly mines";
        QMessageBox::information(this, "Minesweeper", to_show, QMessageBox::Ok);
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString newseed = ui->seedEdit->text();
    int numseed = newseed.toInt(); // if there was text, then numseed = 0
    for(int i=0; i<field->size(); i++)
    {
        for(int j=0; j<field->at(i).size(); j++)
        {
            delete field->at(i).at(j);
        }
    }
    delete gmbd;
    delete gelapsed;
    delete field;
    if(field_size != 15)
    {
        field_size += 3;
    }
    else
    {
        field_size = 6;
    }
    prepare_playground(numseed);
}

