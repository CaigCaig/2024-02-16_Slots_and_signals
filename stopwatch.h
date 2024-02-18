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

private:
    //int h, m, s, ms, laps, total_sec, last_lap;
    //QString m_s, s_s;
    int ticks;
    bool start_stop;
    QTimer *timer;

private slots:
    void TimerAlarm();

signals:
    void sig_start_stop();
    void sig_SendTime(int);

};

#endif // STOPWATCH_H
