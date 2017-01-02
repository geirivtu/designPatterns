#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QObject>
#include <QVariant>

class QTimer;

class StateMachine : public QObject
{
    Q_OBJECT
public:
    explicit StateMachine(QObject *parent = 0);
    ~StateMachine();

    /*!
     * \brief The StateEnum enum defines the internal states of the StateMachine
     */
    enum StateEnum
    {
        STOPPED,
        RUNNING,
        PAUSED
    };
    QString stateString(StateEnum state);

    /*!
     * \brief   The SignalEnum enum defines the internal signals used in the StateMachine
     *
     *          Each possible input signal is given an internal signal definition, in order to process
     *          all incoming signals according to the current generator state
     */
    enum SignalEnum
    {
        START,
        PAUSE,
        STOP,
        TICK
    };
    QString signalString(SignalEnum signal);

signals:

    void timerValue(int value);

private slots:

    void play();
    void pause();
    void stop();

    //Internal
    void tick();

private:

    QTimer *timerSecTick_;

    //State variables
    int time_;

    //State handling routines
    StateEnum state_;

    void handleInput(SignalEnum, QVariant param = QVariant());
    void handleState_STOPPED(SignalEnum signal, QVariant param);
    void handleState_RUNNING(SignalEnum signal, QVariant param);
    void handleState_PAUSED(SignalEnum signal, QVariant param);

};

#endif // STATEMACHINE_H
