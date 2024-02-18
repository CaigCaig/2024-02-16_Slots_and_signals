#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pb_clear->setText("Очистить");
    ui->pb_lap->setText("Круг");
    ui->pb_start_stop->setText("Старт");

    QFont font("Tahoma", 28, QFont::Bold);
    ui->lb_time->setFont(font);
    ui->lb_time->setText("чч:мм:сс:мс");

    ui->pb_lap->setDisabled(true);

    sw = new Stopwatch(this);

    connect(sw, &Stopwatch::sig_SendTime, this, &MainWindow::ReceiveTime);

    h = 0;
    m = 0;
    s = 0;
    ms = 0;
    laps = 0;
    lap_time = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_start_stop_clicked()
{
    if (ui->pb_start_stop->text() == "Старт")
    {
        ui->pb_lap->setDisabled(false);
        ui->pb_start_stop->setText("Стоп");
    }
    else
    {
        h = 0;
        m = 0;
        s = 0;
        ms = 0;
        laps = 0;
        lap_time = 0;
        ui->pb_lap->setDisabled(true);
        ui->pb_start_stop->setText("Старт");
    }
    if (ui->pb_start_stop)
        sw->SendStartStop();
}

void MainWindow::on_pb_clear_clicked()
{
    h = 0;
    m = 0;
    s = 0;
    ms = 0;
    laps = 0;
    lap_time = 0;
    ui->lb_time->setText("0ч 00м 00с 0");
    ui->tb_laps->clearHistory();
    sw->SW_Clear();
}

void MainWindow::on_pb_lap_clicked()
{
    laps++;
    lap_time = static_cast<int>((lap_time+5)/10);
    ui->tb_laps->append(QString("Круг %1, время: %2 сек").arg(laps).arg(lap_time));
    lap_time = 0;
}

void MainWindow::ReceiveTime(int time)
{
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
    ui->lb_time->setText(QString::number(h) + "ч " + m_s + "м " + s_s + "с " + QString::number(ms));
}
