#include "fatigue.h"
#include <QDebug>

Fatigue::Fatigue(QObject *parent) :
    QObject(parent)
{
}

 void Fatigue::calculate(QList<int> segment)
{
    //qDebug() << "Calculate fatigue ";
    int counter = 0;
    int total = 0;
    for (int i = 0; i < segment.size(); i++) {
        counter++;
        total += segment.value(i);
    }

    if (counter > 0) {
        float average = (total / counter);
        qDebug() << "The average for this segment is " << average;
        emit new_average(average);
    }
}
