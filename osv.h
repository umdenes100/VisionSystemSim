#ifndef OSV_H
#define OSV_H

#include <QObject>
#include <QPoint>
#include <QImage>
#include <QDebug>
#include <QPen>
#include <QPainter>
#include <QSettings>
#include <QRandomGenerator>
#include <algorithm>

#include "detail.h"

#define TANK_SPEED 0.35
#define ROTATIONS_PER_SECOND 0.16
#define WOOD_WIDTH 120
#define MARKER_WIDTH 100



class OSV : public QObject
{
    Q_OBJECT
public:
    explicit OSV(QObject *parent = nullptr);
    void refreshLocation();
    Point location, prevLocation, startingLocation, destination;
    bool sensors[12];
    double length, width;
    void setRightPWM(int pwm);
    void setLeftPWM(int pwm);
    void setLocation(Point p);
    double ppm;
    QImage draw();
    QImage osvImage;
    void toggleSensor(int index);
    int leftPWM, rightPWM;

signals:

public slots:
    void writeSettings();

private:
    QRandomGenerator gen = QRandomGenerator::securelySeeded();
    std::default_random_engine rand_eng;
    int prevLeftPWM, prevRightPWM;
    const QColor treadColor = QColor(80,80,80);
    void readSettings();
};

#endif // OSV_H
