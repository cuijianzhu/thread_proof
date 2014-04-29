#include <QDebug>

#include "tobii.h"
#include "pthread.h"
#include <errno.h>

Tobii::Tobii(QObject *parent) :
    QObject(parent)
{
    pthread_t th;
    pthread_mutex_t mxq; /* mutex used as quit flag */
    QList<int> treadmill;

    struct stuff things;
    things.mt = mxq;
    things.data_list = treadmill;
}

void Tobii::start(Fatigue &factor)
{
    qDebug() << "Start the device.";

    things.fatigue = &factor;

    pthread_mutex_init(&things.mt,NULL);
    pthread_mutex_lock(&things.mt);

    pthread_create(&th,NULL,&write,&things);
    pthread_create(&th,NULL,&read,&things);
}

void Tobii::stop()
{
    qDebug() << "Stop the device";

    pthread_mutex_unlock(&things.mt);
    pthread_join(th,NULL);
}

void *Tobii::write(void *arg)
{
    struct stuff *args = (struct stuff *)arg;
    int i = 0;
    while(needQuit(&args->mt) == 0) {
        *&args->data_list += i;
        i++;
        usleep(33);
      //  qDebug() << "Writing see the data list as " << args->data_list.size() << "in size.";
    }
    return 0;
}

void *Tobii::read(void *arg)
{
   struct stuff *args = (struct stuff *)arg;
   QList<int> segment;
   while(needQuit(&args->mt) == 0) {
       if (!args->data_list.isEmpty() && segment.size() < 30) {
           segment += args->data_list.takeFirst();
       }
      // qDebug() << "Reading see the segment as " << segment.size() << "in size.";

       if (segment.size() == 30) {
           args->fatigue->calculate(segment);
           segment.clear();
       }
   }
   return 0;
}

/* Returns 1 (true) if the mutex is unlocked, which is the
 * thread's signal to terminate.
 */
int Tobii::needQuit(pthread_mutex_t *mtx)
{

  int val = pthread_mutex_trylock(mtx);

  switch(val) {
    case 0: /* if we got the lock, unlock and return 1 (true) */
      pthread_mutex_unlock(mtx);
      return 1;
    case EBUSY: /* return 0 (false) if the mutex was locked */
      return 0;
  }
  return 1;
}
