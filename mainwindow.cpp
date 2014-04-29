#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Tobii device;
    Fatigue factor;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnStart_clicked()
{
    qDebug() << "Start Button Pushed";
    device.start(factor);
}

void MainWindow::on_btnStop_clicked()
{
    qDebug() << "Stop Button Pushed";
    device.stop();
}
