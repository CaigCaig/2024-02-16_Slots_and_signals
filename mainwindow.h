#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ReceiveTime(int time);

private:
    Ui::MainWindow *ui;
    Stopwatch *sw;
    int h, m, s, ms, laps, lap_time;
    QString m_s, s_s;

signals:
    void send_start_stop();
    void send_clear();
    void send_lap();

private slots:
    void on_pb_start_stop_clicked();
    void on_pb_clear_clicked();
    void on_pb_lap_clicked();
};
#endif // MAINWINDOW_H
