#include <QDebug>

#include "tobii.h"

Tobii::Tobii(QObject *parent) :
    QObject(parent)
{
    pthread_t th;
    QList<float> treadmill;

    struct stuff things;
    things.data_list = treadmill;
}

void Tobii::start(Fatigue *factor)
{
    qDebug() << "Start the device.";

    things.fatigue = factor;

    const int urlSize = 256;
    char url[urlSize];
    tobiigaze_error_code error_code;

    tobiigaze_get_connected_eye_tracker(url, urlSize, &error_code);
    if (error_code) {
        exit(-1);
    }

    eye_tracker = tobiigaze_create(url, &error_code);
    things.tracker = eye_tracker;

    tobiigaze_set_logging("gazelog.log", TOBIIGAZE_LOG_LEVEL_DEBUG, &error_code);
    tobiigaze_run_event_loop_on_internal_thread(eye_tracker, 0, 0);
    tobiigaze_connect(eye_tracker, &error_code);

   // pthread_create(&th,NULL,&write,&things);
    tobiigaze_start_tracking(eye_tracker, &on_gaze_data, &error_code, &things);
    pthread_create(&th,NULL,&read,&things);
}

void Tobii::stop()
{
    qDebug() << "Stop the device";

    tobiigaze_stop_tracking(eye_tracker, &error_code);
    tobiigaze_disconnect(eye_tracker);
    tobiigaze_break_event_loop(eye_tracker);
    tobiigaze_destroy(eye_tracker);

   // qDebug() << "When I stop I left the following " << things.data_list.size() << "in size.";
}

void Tobii::on_gaze_data(const tobiigaze_gaze_data* gazedata, const tobiigaze_gaze_data_extensions* extensions, void *user_data)
{
    struct stuff *args = (struct stuff *)user_data;
   // qDebug() << "On Gaze see the data list as " << args->data_list.size() << "in size.";
    float right_openness = 0;
    //qDebug() << "Inside the loop";
    for (int i = 0; i < (int)extensions->actual_size; ++i) {
        tobiigaze_error_code ec;
            if(extensions->extensions[i].column_id == RIGHT_OPENNESS_COLUMN_ID) {
                right_openness = tobiigaze_gaze_data_extension_to_float(&extensions->extensions[i], &ec);
            }
    }

    *&args->data_list += right_openness;
}

void *Tobii::read(void *arg)
{
   struct stuff *args = (struct stuff *)arg;
   QList<float> segment;
   while (tobiigaze_is_connected(args->tracker)) {
         if (!args->data_list.isEmpty()) {
            segment += args->data_list.takeFirst();

         if (segment.size() == 30) {
            args->fatigue->calculate(segment);
            segment.clear();
         }
        }
   }

   if (!segment.isEmpty())
        args->fatigue->calculate(segment);

  // qDebug() << "I am about to end";
   pthread_exit(NULL);
   return 0;
}
