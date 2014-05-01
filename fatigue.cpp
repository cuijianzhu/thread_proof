#include "fatigue.h"
#include <QDebug>

Fatigue::Fatigue(QObject *parent) :
    QObject(parent)
{
    factor = getBaseFactor();
}

 void Fatigue::calculate(QList<float> segment)
{
     setAverageEyeRatio(segment);
     int perclos_result = 0;
     int segment_size = segment.size();
     float current_barrier = getAverageEyeRatio() * getEyeRatioBarrier();

     for (int i=0; i < segment_size; i++) {
         float eyeReading = segment.value(i);
         if (eyeReading < current_barrier)
         {
             perclos_result++;
         }
      }
      perclos = qRound((perclos_result / (float)segment_size) * 100.00);

      setFatigueFactor(perclos);
}

 int Fatigue::getBaseFactor()
 {
     return 10;
 }

 float Fatigue::getEyeRatioBarrier()
 {
     return ((float)(100 - 80) * .01);;
 }

 float Fatigue::getPerclosPercentage()
 {
     return 80;
 }

 void Fatigue::setAverageEyeRatio(QList<float> current_segment)
 {
    // qDebug() << " Size of current readEyeRaitos is " << readEyeRatios.size();

     // do I need to use this segment
     if (readEyeRatios.size() <= 3600) {
         // cacluate new avearge_eye_ratio
         readEyeRatios += current_segment;
         float total = 0;
         for (int i =0; i < readEyeRatios.size(); i++) {
             total += readEyeRatios.value(i);
         }
         average_eye_ratio = total / readEyeRatios.size();
     }
 }

 float Fatigue::getAverageEyeRatio()
 {
     return average_eye_ratio;
 }

 void Fatigue::setFatigueFactor(float perclos)
 {
     if (perclos <= getPerclosPercentage() && factor > getBaseFactor()) {
         factor -= calculate_alert_rating();
     } else if (perclos > getPerclosPercentage() && factor < 100) {
         factor += 10;
     } else if (perclos == 100.00 && factor < getYellowBoundry()) {
         factor += 20;
     }
     qDebug() << "Fatigue factor was set to " << factor;
     emit factor_changed(factor);
 }

 float Fatigue::getPerclos()
 {
     return perclos;
 }

 int Fatigue::getYellowBoundry()
 {
     return 50;
 }

 int Fatigue::getRedBoundry()
 {
     return 80;
 }

 int Fatigue::calculate_alert_rating()
 {
     int alert_rate = 0;
     int base_rate = 1;
     int yellow_rate = 15;
     int red_rate = 25;

     if (factor < getYellowBoundry()) {
         alert_rate = base_rate;
     } else if (factor > getRedBoundry()) {
         alert_rate = red_rate;
     } else {
         alert_rate = yellow_rate;
     }
     return alert_rate;
 }
