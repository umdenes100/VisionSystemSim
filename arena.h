#ifndef ARENA_H
#define ARENA_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <stdlib.h>
#include <QLineF>
#include <QPointF>
#include <math.h>

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
    QPoint metersToPixels(Point inMeters);
    int metersToPixels(float length);
    float getDistance(int index);
    Point destination;
    Point startingLocation;
    int getEntropy();

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
    void entropyChanged(int newEntropy);

private:
    Ui::Arena *ui;
    void paintEvent(QPaintEvent *event);
    void updateDestination();
    QTimer* refreshTimer;
    QTime timeElapsed;
    int arenaWidthPx, arenaHeightPx;
    int xOffsetPx, yOffsetPx;
    int entropy;
    inline float distance(Point a, QPointF *b);
};

#endif // ARENA_H
