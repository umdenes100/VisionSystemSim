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

#define DEFAULT_WIDTH 0.229
#define DEFAULT_LENGTH 0.239
#define TANK_SPEED 0.35
#define ROTATIONS_PER_SECOND 0.16
#define ENTROPY_STDDEV 0.06
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
    double length, width;
    void setRightPWM(int pwm, bool entropy);
    void setLeftPWM(int pwm, bool entropy);
    void setLocation(Point p);
    double ppm;
    QImage draw();
    QImage osvImage;
    void toggleSensor(int index);
    int leftPWM, rightPWM;

signals:

public slots:

private:
    int prevLeftPWM, prevRightPWM;
    const QColor treadColor = QColor(80,80,80);
};

#endif // OSV_H
