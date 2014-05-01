#ifndef TOBII_H
#define TOBII_H

#include <QObject>
#include <QList>

#include "tobiigaze_discovery.h"
#include "tobiigaze_ext.h"
#include "tobiigaze_error_codes.h"
#include "tobiigaze.h"
#include "tobiigaze_data_types.h"
#include "tobiigaze_callback_types.h"

#include "pthread.h"
#include <errno.h>

#include "fatigue.h"

struct stuff {
    QList<float> data_list;
    tobiigaze_eye_tracker* tracker;
    Fatigue *fatigue;
};

enum {
    LEFT_OPENNESS_COLUMN_ID = 18,
    RIGHT_OPENNESS_COLUMN_ID = 19,
};
class Tobii : public QObject
{
    Q_OBJECT
public:
    explicit Tobii(QObject *parent = 0);

    struct stuff things;

    void start(Fatigue *factor);
    void stop();

protected:

    pthread_t th;
    QList<float> treadmill;

    tobiigaze_error_code error_code;
    tobiigaze_eye_tracker* eye_tracker;



    static void on_gaze_data(const tobiigaze_gaze_data* gazedata, const tobiigaze_gaze_data_extensions* extensions, void *user_data);
    static void *read(void * arg);

signals:

public slots:

};

#endif // TOBII_H
