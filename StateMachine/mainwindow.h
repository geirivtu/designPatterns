#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class StateMachine;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void setTimerValue(int value);

private:
    Ui::MainWindow *ui;


    StateMachine *stateMachine_;

    void initStateMachine();
};

#endif // MAINWINDOW_H
