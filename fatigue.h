#ifndef FATIGUE_H
#define FATIGUE_H

#include <QObject>
#include <QList>

class Fatigue : public QObject
{
    Q_OBJECT
public:
    explicit Fatigue(QObject *parent = 0);

    void calculate(QList<int> segment);

signals:

public slots:

};

#endif // FATIGUE_H