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

    Tobii device;
    Fatigue risk;

protected:


private slots:
    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void change_factor(int value);

signals:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
