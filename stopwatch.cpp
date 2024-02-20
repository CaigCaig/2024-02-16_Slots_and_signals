#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}
{
    start_stop = false;
    h = 0;
    m = 0;
    s = 0;
    ms = 0;
    laps = 0;
    lap_time = 0;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [this]{TimerAlarm();});
}

Stopwatch::~Stopwatch()
{
    qDebug() << "Call Stopwatch Destructor";
}

void Stopwatch::SendStartStop()
{
    if (start_stop == false)
    {
        h = 0;
        m = 0;
        s = 0;
        ms = 0;
        laps = 0;
        lap_time = 0;
        start_stop = true;
        timer->start(100);
    }
    else
    {
        start_stop = false;
        timer->stop();
    }
}

void Stopwatch::SendLap()
{
    laps++;
    lap_time = static_cast<int>((lap_time+5)/10);
    lap_str = (QString("Круг %1, время: %2 сек").arg(laps).arg(lap_time));
    lap_time = 0;
    emit sig_Lap(lap_str);
}

void Stopwatch::TimerAlarm()
{
    ticks++;
    lap_time++;
    ms++;
    if (ms >=10)
    {
        ms = 0;
        s++;
        if (s>=60)
        {
            s = 0;
            m++;
            if (m>=60)
            {
                m = 0;
                h++;
            }
        }
    }
    m_s = "";
    if (m < 10)
    {
        m_s = "0";
    }
    m_s += QString::number(m);

    s_s = "";
    if (s < 10)
    {
        s_s = "0";
    }
    s_s += QString::number(s);
    timer_str = QString::number(h) + "ч " + m_s + "м " + s_s + "с " + QString::number(ms);
    emit sig_SendTime(timer_str);
}


void Stopwatch::SW_Clear()
{
    ticks = 0;
    h = 0;
    m = 0;
    s = 0;
    ms = 0;
    laps = 0;
    lap_time = 0;
}
