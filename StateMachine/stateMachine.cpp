#include "stateMachine.h"

#include <QDebug>

StateMachine::StateMachine(QObject *parent) :
    QObject(parent),
    m_state(STOPPED)
{

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
    default:
        return QString("[Unknown signal: %1]").arg((int)signal);
    }
}

void StateMachine::handleInput(StateMachine::SignalEnum signal, QVariant param)
{
    qDebug() << "Received input signal: " << signalString(signal) << " in state: " << stateString(m_state);

    switch(m_state)
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
        qDebug() <<  QString("Received signal %1 in invalid state: %2").arg(signalString(signal)).arg((int)m_state);
    }
}

void StateMachine::handleState_STOPPED(StateMachine::SignalEnum signal, QVariant param)
{
    switch(signal)
    {
    case StateMachine::START:
        m_state = RUNNING;
        break;
    case StateMachine::PAUSE:
        break;
    case StateMachine::STOP:
        break;

    default:
        qDebug() << QString("Received invalid signal %1 in state %2").arg((int)signal).arg(stateString(m_state));
    }
}

void StateMachine::handleState_RUNNING(StateMachine::SignalEnum signal, QVariant param)
{
    switch(signal)
    {
    case StateMachine::START:
        break;
    case StateMachine::PAUSE:
        break;
    case StateMachine::STOP:
        break;

    default:
        qDebug() << QString("Received invalid signal %1 in state %2").arg((int)signal).arg(stateString(m_state));
    }
}

void StateMachine::handleState_PAUSED(StateMachine::SignalEnum signal, QVariant param)
{
    switch(signal)
    {
    case StateMachine::START:
        break;
    case StateMachine::PAUSE:
        break;
    case StateMachine::STOP:
        break;

    default:
        qDebug() << QString("Received invalid signal %1 in state %2").arg((int)signal).arg(stateString(m_state));
    }
}
