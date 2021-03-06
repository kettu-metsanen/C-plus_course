#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>
#include <QMouseEvent>
#include "gameboard.hh"
#include "qextendedbutton.hh"
#include <QTimer>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool cancelled_at_start;

private slots:
    void left_clicked();
    void right_clicked();
    void tick_time();

    void on_resetButton_clicked();

    void on_isokButton_clicked();

    void on_pushButton_clicked();

signals:

private:
    Ui::MainWindow *ui;
    QVector<QVector<QExtendedButton*>> *field;
    GameBoard *gmbd;
    QIcon icflag;
    QIcon icdot;
    QIcon icmine;
    QIcon icquestion;
    QTimer *gelapsed;
    int field_size;
    void check_game_over();
    int mins;
    int secs;
    void prepare_playground(int seed);

};
#endif // MAINWINDOW_HH
