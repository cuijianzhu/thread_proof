#ifndef TOBII_H
#define TOBII_H

#include <QObject>
#include <QList>
#include "pthread.h"
#include "fatigue.h"

struct stuff {
    pthread_mutex_t mt;
    QList<int> data_list;
    Fatigue *fatigue;
};

class Tobii : public QObject
{
    Q_OBJECT
public:
    explicit Tobii(QObject *parent = 0);

    void start(Fatigue &factor);
    void stop();

protected:

    pthread_t th;
    pthread_mutex_t mxq;
    QList<int> treadmill;

    struct stuff things;

    static void *write(void *arg);
    static void *read(void * arg);
    static int needQuit(pthread_mutex_t *mtx);

signals:

public slots:

};

#endif // TOBII_H
