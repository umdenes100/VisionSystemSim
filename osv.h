#ifndef OSV_H
#define OSV_H

#include <QObject>
#include <QPoint>
#include <QImage>
#include <QDebug>
#include <QPen>
#include <QPainter>
#include <random>
#include <algorithm>

#include "detail.h"
#define TANK_SPEED 0.35f
#define ROTATIONS_PER_SECOND 0.16f
#define WOOD_WIDTH 120
#define MARKER_WIDTH 100



class OSV : public QObject
{
    Q_OBJECT
public:
    explicit OSV(QObject *parent = nullptr);
    void refreshLocation();
    Point location;
    Point prevLocation;
    bool sensors[12];
    Point startingLocation;
    Point destination;
    float length, width;
    void setRightPWM(int pwm, int entropy);
    void setLeftPWM(int pwm, int entropy);
    void setLocation(Point p);
    float ppm;
    QImage draw();
    QImage osvImage;
    void toggleSensor(int index);
    int leftPWM, rightPWM;

signals:

public slots:

private:
    int prevLeftPWM, prevRightPWM;
};

#endif // OSV_H
