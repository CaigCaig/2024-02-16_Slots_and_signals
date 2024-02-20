#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QTime>

class Stopwatch : public QObject
{
    Q_OBJECT

    typedef enum
    {
        stop = false,
        start = true
    } start_stop_t;

public:
    explicit Stopwatch(QObject *parent = nullptr);
    ~Stopwatch();
    void SW_Clear();

public slots:
    void SendStartStop();
    void SendLap();

private:
    int h, m, s, ms, laps, lap_time;
    QString m_s, s_s, timer_str, lap_str;
    int ticks;
    bool start_stop;
    QTimer *timer;

private slots:
    void TimerAlarm();

signals:
    void sig_start_stop();
    void sig_SendTime(QString);
    void sig_Lap(QString);
    void sig_Clear();

};

#endif // STOPWATCH_H

