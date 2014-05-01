#ifndef FATIGUE_H
#define FATIGUE_H

#include <QObject>
#include <QList>

class Fatigue : public QObject
{
    Q_OBJECT
public:
    int base_factor;
    int factor;
    float perclos;
    float base_eye_ratio_barrier;
    int perclos_percentage;
    float average_eye_ratio;
    QList<float> readEyeRatios;

    explicit Fatigue(QObject *parent = 0);
    void calculate(QList<float> segment);

    int getBaseFactor();
    float getEyeRatioBarrier();
    float getPerclosPercentage();
    int getYellowBoundry();
    int getRedBoundry();

    void setAverageEyeRatio(QList<float> current_segment);
    float getAverageEyeRatio();

    void setFatigueFactor(float perclos);
    int getFatigueFactor();

    void setPerclos(QList<float> segment);
    float getPerclos();

    int calculate_alert_rating();

signals:
    void factor_changed(int value);

public slots:

};

#endif // FATIGUE_H
