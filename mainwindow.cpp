#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Tobii device;
 //   Fatigue factor;

    connect(&factor, SIGNAL(new_average(float)), this, SLOT(display_new_average(float)), Qt::DirectConnection);
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

void MainWindow::display_new_average(float average)
{
    ui->lblAverage->setText(QString::number(average));
}

void MainWindow::on_btnStop_clicked()
{
    qDebug() << "Stop Button Pushed";
    device.stop();
}
