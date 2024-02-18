#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}
{
    start_stop = false;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerAlarm()));
}

Stopwatch::~Stopwatch()
{
    qDebug() << "Call Stopwatch Destructor";
}

void Stopwatch::SendStartStop()
{
    if (start_stop == false)
    {
        start_stop = true;
        timer->start(100);
    }
    else
    {
        start_stop = false;
        timer->stop();
    }
}

void Stopwatch::TimerAlarm()
{
    emit sig_SendTime(++ticks);
}


void Stopwatch::SW_Clear()
{
    ticks = 0;
}
