#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tobii.h"
#include "fatigue.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    Tobii device;
    Fatigue factor;

private slots:
    void on_btnStart_clicked();

    void on_btnStop_clicked();

signals:
    void send_segment(QList<int> segment);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
