#ifndef OSV_H
#define OSV_H

#include <QObject>
#include <QPoint>
#include <QImage>
#include <QDebug>
#include <QPen>
#include <QPainter>

#include "detail.h"
#define TANK_SPEED 0.35
#define ROTATIONS_PER_SECOND 0.16

class OSV : public QObject
{
    Q_OBJECT
public:
    explicit OSV(QObject *parent = nullptr);
    void refreshLocation();
    Point location;
    Point prevLocation;
    bool sensors[9];
    Point startingLocation;
    Point destination;
    float length, width;
    void setRightPWM(int pwm);
    void setLeftPWM(int pwm);
    void setLocation(Point p);
    float ppm;
    QImage draw();
    QImage osvImage;
    void toggleSensor(int index);

signals:

public slots:

private:
    int leftPWM, rightPWM;
};

#endif // OSV_H
