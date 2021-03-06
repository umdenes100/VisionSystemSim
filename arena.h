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
#include <QHelpEvent>
#include <QToolTip>
#include <QSettings>

#include "osv.h"
#include "detail.h"

#define OBSTACLE_WIDTH 0.2
#define OBSTACLE_HEIGHT 0.5
#define OSV_WIDTH 0.35
#define TARGET_DIAMETER 0.18

namespace Ui {
class Arena;
}

class Arena : public QWidget
{
    Q_OBJECT

public:
    explicit Arena(QWidget *parent = nullptr);
    ~Arena();
    OSV* osv;
    QPoint metersToPixels(Point inMeters);
    int metersToPixels(double length);
    double getDistance(int index);
    Point destination, startingLocation;
    bool getEntropy();
    bool entropyEnabled = false;
    bool obstaclesEnabled = true;
    struct Obstacle {
        Point location;
        double length, width;
    };

public slots:
    void writeSettings();

private slots:
    void timerTick();
    void refresh();
    void randomize();
    void reset();
    void entropyChanged(bool enabled);
    void obstaclesToggled(bool enabled);

private:
    Ui::Arena *ui;
    void paintEvent(QPaintEvent *event);
    void updateDestination();
    bool event(QEvent* event);
    bool checkForCollisions();
    void readSettings();

    QTimer* refreshTimer;
    QTime timeElapsed;
    int arenaWidthPx, arenaHeightPx;
    int xOffsetPx, yOffsetPx;
    inline double distance(Point a, QPointF *b);
    const QColor sandColor = QColor(250, 226, 190);
    const QColor obstacleColor = QColor(150, 126, 90);
    const QColor terrainColor = QColor(210, 186, 150);
    Obstacle obstacles[3];

};

#endif // ARENA_H
