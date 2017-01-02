#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <QObject>
#include <QVariant>

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
        STOP
    };
    QString signalString(SignalEnum signal);

signals:

public slots:

private:

    //State handling routines
    StateEnum m_state;

    void handleInput(SignalEnum, QVariant param = QVariant());
    void handleState_STOPPED(SignalEnum signal, QVariant param);
    void handleState_RUNNING(SignalEnum signal, QVariant param);
    void handleState_PAUSED(SignalEnum signal, QVariant param);

};

#endif // STATEMACHINE_H
