#ifndef ARENA_H
#define ARENA_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <stdlib.h>
#include <QLineF>

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
    Point destination;
    Point startingLocation;

    struct Obstacle {
        Point location;
        float length, width;
    };

    Obstacle obstacles[3];

private slots:
    void refresh();
    void randomize();

private:
    Ui::Arena *ui;
    void paintEvent(QPaintEvent *event);
    void updateDestination();
    QTimer* refreshTimer;
    int arenaWidthPx, arenaHeightPx;
    int xOffsetPx, yOffsetPx;

    inline float max(float a, float b);
    inline float min(float a, float b);
};

#endif // ARENA_H
