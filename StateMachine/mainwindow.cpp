
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "stateMachine.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    initStateMachine();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTimerValue(int value)
{
    ui->lcdNumber_time->display(value);
}

void MainWindow::initStateMachine()
{
    stateMachine_ = new StateMachine(this);

    //STATE MACHINE INPUT
    connect(ui->pushButton_play, SIGNAL(clicked(bool)),
            stateMachine_,       SLOT(play()));

    connect(ui->pushButton_pause, SIGNAL(clicked(bool)),
            stateMachine_,       SLOT(pause()));

    connect(ui->pushButton_stop, SIGNAL(clicked(bool)),
            stateMachine_,       SLOT(stop()));



    //OUTPUT

    connect(stateMachine_, SIGNAL(timerValue(int)),
            this,          SLOT(setTimerValue(int)));
}
