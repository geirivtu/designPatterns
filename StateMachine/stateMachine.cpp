#include "stateMachine.h"

#include <QDebug>
#include <QTimer>


StateMachine::StateMachine(QObject *parent) :
    QObject(parent),
    state_(STOPPED)
{
    timerSecTick_ = new QTimer(this);

    connect(timerSecTick_, SIGNAL(timeout()),
            this,          SLOT(tick()));

    timerSecTick_->start(1000);

}

StateMachine::~StateMachine()
{

}

QString StateMachine::stateString(StateEnum state)
{
    switch(state)
    {
    case StateMachine::STOPPED:
        return "STOPPED";
        break;
    case StateMachine::RUNNING:
        return "RUNNING";
        break;
    case StateMachine::PAUSED:
        return "PAUSED";
        break;
    default:
        return QString("[Unknown state: %1]").arg((int)state);
    }
}

QString StateMachine::signalString(StateMachine::SignalEnum signal)
{
    switch(signal)
    {
    case StateMachine::START:
        return "START";
        break;

    case StateMachine::PAUSE:
        return "PAUSE";
        break;

    case StateMachine::STOP:
        return "STOP";
        break;
    case StateMachine::TICK:
        return "TICK";
        break;
    default:
        return QString("[Unknown signal: %1]").arg((int)signal);
    }
}

void StateMachine::play()
{
    handleInput(START);
}

void StateMachine::pause()
{
    handleInput(PAUSE);
}

void StateMachine::stop()
{
    handleInput(STOP);
}

void StateMachine::tick()
{
    handleInput(TICK);
}

void StateMachine::handleInput(StateMachine::SignalEnum signal, QVariant param)
{
    qDebug() << "Received input signal: " << signalString(signal) << " in state: " << stateString(state_);

    switch(state_)
    {
    case StateMachine::STOPPED:
        handleState_STOPPED(signal, param);
        break;
    case StateMachine::PAUSED:
        handleState_PAUSED(signal, param);
        break;
    case StateMachine::RUNNING:
        handleState_RUNNING(signal, param);
        break;

    default:
        qWarning() <<  QString("Received signal %1 in invalid state: %2").arg(signalString(signal)).arg((int)state_);
    }
}

void StateMachine::handleState_STOPPED(StateMachine::SignalEnum signal, QVariant param)
{
    switch(signal)
    {
    case StateMachine::TICK:
        //Do nothing
        break;
    case StateMachine::START:
        time_ = 0;
        state_ = RUNNING;
        break;
    case StateMachine::PAUSE:
        state_ = PAUSED;
        break;
    case StateMachine::STOP:
        time_ = 0;
        emit timerValue(time_);
        break;

    default:
        qWarning() << QString("Received invalid signal %1 in state %2").arg((int)signal).arg(stateString(state_));
    }
}

void StateMachine::handleState_RUNNING(StateMachine::SignalEnum signal, QVariant param)
{
    switch(signal)
    {
    case StateMachine::TICK:
        time_++;
        emit timerValue(time_);
        break;
    case StateMachine::START:
        //Do nothing
        break;
    case StateMachine::PAUSE:
        state_ = PAUSED;
        break;
    case StateMachine::STOP:
        state_ = STOPPED;
        break;

    default:
        qWarning() << QString("Received invalid signal %1 in state %2").arg((int)signal).arg(stateString(state_));
    }
}

void StateMachine::handleState_PAUSED(StateMachine::SignalEnum signal, QVariant param)
{
    switch(signal)
    {
    case StateMachine::TICK:
        //Do nothing
        break;
    case StateMachine::START:
        state_ = RUNNING;
        break;
    case StateMachine::PAUSE:
        //Do nothing
        break;
    case StateMachine::STOP:
        state_ = STOPPED;
        break;

    default:
        qWarning() << QString("Received invalid signal %1 in state %2").arg((int)signal).arg(stateString(state_));
    }
}
