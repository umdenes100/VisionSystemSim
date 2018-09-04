#ifndef ARENA_H
#define ARENA_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <stdlib.h>
#include <QLineF>
#include <QPointF>

#include "osv.h"
#include "detail.h"

#define TARGET_DIAMETER 0.18

namespace Ui {
class Arena;
}

class Arena : public QWidget
{
    Q_OBJECT

public:
    explicit Arena(QWidget *parent = 0);
    ~Arena();
    OSV* osv;
    bool customShowing = false;
    QPoint metersToPixels(Point inMeters);
    int metersToPixels(float length);
    float getDistance(int index);
    Point destination;
    Point startingLocation;
    Point customCoordinate;

    struct Obstacle {
        Point location;
        float length, width;
    };

    Obstacle obstacles[3];

private slots:
    void timerTick();
    void refresh();
    void randomize();
    void reset();
    void customButtonClicked(int arg1);
    void customCoordinateChanged(float value, bool isX);

private:
    Ui::Arena *ui;
    void paintEvent(QPaintEvent *event);
    void updateDestination();
    QTimer* refreshTimer;
    QTime timeElapsed;
    int arenaWidthPx, arenaHeightPx;
    int xOffsetPx, yOffsetPx;

    inline float max(float a, float b);
    inline float min(float a, float b);
    inline float distance(Point a, QPointF *b);
};

#endif // ARENA_H
