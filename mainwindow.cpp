#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&risk, SIGNAL(factor_changed(int)), this, SLOT(change_factor(int)), Qt::DirectConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnStart_clicked()
{
    qDebug() << "Start Button Pushed";

    device.start(&risk);
}

void MainWindow::on_btnStop_clicked()
{
    qDebug() << "Stop Button Pushed";
    device.stop();
}

void MainWindow::change_factor(int value)
{
    qDebug() << "Something was emited for you.";
    ui->lblAverage->setText(QString::number(value));
}
