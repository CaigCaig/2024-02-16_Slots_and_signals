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
    connect(sw, &Stopwatch::sig_Lap, this, &MainWindow::ReceiveLapData);

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
        ui->pb_lap->setDisabled(true);
        ui->pb_start_stop->setText("Старт");
    }
    if (ui->pb_start_stop)
        sw->SendStartStop();
}

void MainWindow::on_pb_clear_clicked()
{
    ui->lb_time->setText("0ч 00м 00с 0");
    ui->tb_laps->clearHistory();
    sw->SW_Clear();
}

void MainWindow::on_pb_lap_clicked()
{
    sw->SendLap();
}

void MainWindow::ReceiveTime(QString str)
{
    ui->lb_time->setText(str);
}

void MainWindow::ReceiveLapData(QString str)
{
    ui->tb_laps->append(str);
}
