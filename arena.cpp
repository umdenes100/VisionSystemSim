#include "arena.h"
#include "ui_arena.h"

Arena::Arena(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Arena)
{
    osv = new OSV();
    randomize();
    ui->setupUi(this);
    refreshTimer = new QTimer();
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    refreshTimer->start(20);
}

Arena::~Arena()
{
    delete ui;
}

void Arena::refresh()
{
    osv->refreshLocation();


    // we have to get the slope of the front side of the osv first
    Point midPoint;
    midPoint.x = osv->location.x + osv->width / 2 * cos(osv->orientation);
    midPoint.y = osv->location.y + osv->width / 2 * sin(osv->orientation);

    Point a;
    a.x = midPoint.x - osv->length / 2 * sin(osv->orientation);
    a.y = midPoint.y + osv->length / 2 * cos(osv->orientation);

    Point b;
    b.x = midPoint.x + osv->length / 2 * sin(osv->orientation);
    b.y = midPoint.y - osv->length / 2 * cos(osv->orientation);

    Point midPoint2;
    midPoint2.x = osv->location.x - osv->width / 2 * cos(osv->orientation);
    midPoint2.y = osv->location.y - osv->width / 2 * sin(osv->orientation);

    Point c;
    c.x = midPoint2.x - osv->length / 2 * sin(osv->orientation);
    c.y = midPoint2.y + osv->length / 2 * cos(osv->orientation);

    Point d;
    d.x = midPoint2.x + osv->length / 2 * sin(osv->orientation);
    d.y = midPoint2.y - osv->length / 2 * cos(osv->orientation);

    QLineF frontOSV(a.x, a.y, b.x, b.y);
    QLineF leftOSV(a.x, a.y, c.x, c.y);
    QLineF backOSV(c.x, c.y, d.x, d.y);
    QLineF rightOSV(b.x, b.y, d.x, d.y);

    bool collision = false;

    for(int i = 0; i < 3; i++) {
        // for each of the obstacles
        QLineF right(obstacles[i].location.x + obstacles[i].width, obstacles[i].location.y, obstacles[i].location.x + obstacles[i].width, obstacles[i].location.y - obstacles[i].length);
        QLineF bottom(obstacles[i].location.x, obstacles[i].location.y - obstacles[i].length, obstacles[i].location.x + obstacles[i].width, obstacles[i].location.y - obstacles[i].length);
        QLineF left(obstacles[i].location.x, obstacles[i].location.y - obstacles[i].length, obstacles[i].location.x, obstacles[i].location.y);
        QLineF top(obstacles[i].location.x, obstacles[i].location.y, obstacles[i].location.x + obstacles[i].width, obstacles[i].location.y);

        if(right.intersect(frontOSV, NULL) == QLineF::BoundedIntersection) {
            collision = true;
            break;
        }

        if(right.intersect(backOSV, NULL) == QLineF::BoundedIntersection) {
            collision = true;
            break;
        }

        if(left.intersect(frontOSV, NULL) == QLineF::BoundedIntersection) {
            collision = true;
            break;
        }

        if(left.intersect(backOSV, NULL) == QLineF::BoundedIntersection) {
            collision = true;
            break;
        }

        if(top.intersect(frontOSV, NULL) == QLineF::BoundedIntersection) {
            collision = true;
            break;
        }

        if(top.intersect(backOSV, NULL) == QLineF::BoundedIntersection) {
            collision = true;
            break;
        }

        if(bottom.intersect(frontOSV, NULL) == QLineF::BoundedIntersection) {
            collision = true;
            break;
        }

        if(bottom.intersect(backOSV, NULL) == QLineF::BoundedIntersection) {
            collision = true;
            break;
        }
    }

    // now we want to define the walls:
    QLineF right(4.0, 0.0, 4.0, 2.0);
    QLineF bottom(0.0, 0.0, 4.0, 0.0);
    QLineF left(0.0, 0.0, 0.0, 2.0);
    QLineF top(0.0, 2.0, 4.0, 2.0);

    //need to check right and left sides of OSV in case OSV is perpendicular to wall

    if(right.intersect(frontOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(right.intersect(backOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(right.intersect(rightOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(right.intersect(leftOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(left.intersect(frontOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(left.intersect(backOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(left.intersect(rightOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(left.intersect(leftOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(top.intersect(frontOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(top.intersect(backOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(top.intersect(rightOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(top.intersect(leftOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(bottom.intersect(frontOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(bottom.intersect(backOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(bottom.intersect(rightOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }

    if(bottom.intersect(leftOSV, NULL) == QLineF::BoundedIntersection) {
        collision = true;
    }




    if(collision) {
        osv->location.x = osv->prevLocation.x;
        osv->location.y = osv->prevLocation.y;
        osv->orientation = osv->prevLocation.theta;
    }

    update();
}

void Arena::paintEvent(QPaintEvent *event)//why does this method need a parameter?
{
    QPainter paint(this);
    QPen pen(Qt::black);
    //QPen brownPen();

    pen.setWidth(2);
    paint.setPen(pen);

    // TODO: draw background

    if((float)(width() + 2 * xOffsetPx) / (float)(height() + 2 * yOffsetPx) < 2) {
        arenaWidthPx = width() - 60;
        arenaHeightPx = arenaWidthPx / 2;

        xOffsetPx = 30;
        yOffsetPx = height() / 2 - arenaHeightPx / 2;
        paint.fillRect(xOffsetPx, yOffsetPx, arenaWidthPx, arenaHeightPx, QColor(250, 226, 190));
        paint.drawRect(xOffsetPx, yOffsetPx, arenaWidthPx, arenaHeightPx);
    } else {
        arenaHeightPx = height() - 60;
        arenaWidthPx = arenaHeightPx * 2;

        yOffsetPx = 30;
        xOffsetPx = width() / 2 - arenaWidthPx / 2;
        paint.fillRect(xOffsetPx, yOffsetPx, arenaWidthPx, arenaHeightPx, QColor(250, 226, 190));
        paint.drawRect(xOffsetPx, yOffsetPx, arenaWidthPx, arenaHeightPx);
    }

    osv->ppm = arenaWidthPx / 4.0;

    QImage osvImage = osv->draw();

    paint.drawImage(metersToPixels(osv->location) - osvImage.rect().center(), osvImage);

    for(int i = 0; i < 3; i++) {
        paint.fillRect(metersToPixels(obstacles[i].location).x(), metersToPixels(obstacles[i].location).y(), metersToPixels(obstacles[i].width), metersToPixels(obstacles[i].length), QColor(170, 146, 110));
    }

    paint.drawEllipse(metersToPixels(destination), metersToPixels(TARGET_DIAMETER / 2), metersToPixels(TARGET_DIAMETER / 2));
}

int Arena::metersToPixels(float length)
{
    return (int)(length * arenaWidthPx / 4.0);
}

QPoint Arena::metersToPixels(Point inMeters)
{
    QPoint inPixels;
    inPixels.setX(xOffsetPx + arenaWidthPx * (inMeters.x / 4.0));
    inPixels.setY(yOffsetPx + arenaHeightPx - arenaHeightPx * (inMeters.y / 2.0));

    return inPixels;
}

void Arena::updateDestination()
{
    destination.x = 0;
    destination.y = 0;
    osv->destination = destination;
}

void Arena::randomize()
{
    static const float quadrantBounds[4][4] = {
        // Min x, Max x, Min y, Max y
        {1.35, 2.25, 1.0, 1.8},
        {1.35, 2.25, 0.2, 1.0},
        {2.25, 3.8, 0.2, 1.0},
        {2.25, 3.8, 1.0, 1.8}
    };

    // Generate a random starting position
    startingLocation.x = 0.35;
    startingLocation.y = 0.4 + (rand() % 5) * 0.3;
    startingLocation.theta = (rand() % 4) * PI / 2 - PI;

    // Generate random positions and orientations for obstacles
    int largeObstacleQuadrant = rand() % 3;
    for (int i = 0; i < 3; i++) {
        // Reassign sizes based on randomization
        float d1 = i == largeObstacleQuadrant ? 0.41 : 0.32;
        float d2 = i == largeObstacleQuadrant ? 0.23 : 0.13;

        // Random orientation
        if (rand() % 2) {
            obstacles[i].width = d1;
            obstacles[i].length = d2;
        } else {
            obstacles[i].width = d2;
            obstacles[i].length = d1;
        }
    }

    for (int i = 0; i < 2; i++) {
        // Randomize locations
        obstacles[i].location.x =
                (rand() % 100) *
                (quadrantBounds[i][1] - quadrantBounds[i][0] - obstacles[i].width) / 100.0 +
                quadrantBounds[i][0];
        obstacles[i].location.y =
                (rand() % 100) *
                (quadrantBounds[i][3] - quadrantBounds[i][2] - obstacles[i].length) / 100.0 +
                quadrantBounds[i][2] + obstacles[i].length;
    }

    // Randomize target quadrant (and place obstacle opposite)
    if (rand() % 2) {
        destination.x =
                (rand() % 100) *
                (quadrantBounds[2][1] - quadrantBounds[2][0] - TARGET_DIAMETER) / 100.0 +
                quadrantBounds[2][0] + TARGET_DIAMETER;
        destination.y =
                (rand() % 100) *
                (quadrantBounds[2][3] - quadrantBounds[2][2] - TARGET_DIAMETER) / 100.0 +
                quadrantBounds[2][2] + TARGET_DIAMETER;
        obstacles[2].location.x =
                (rand() % 100) *
                (quadrantBounds[3][1] - quadrantBounds[3][0] - obstacles[2].width) / 100.0 +
                quadrantBounds[3][0];
        obstacles[2].location.y = max(
                (rand() % 100) *
                (quadrantBounds[3][3] - quadrantBounds[3][2] - obstacles[2].length) / 100.0 +
                quadrantBounds[3][2] + obstacles[2].length,
                destination.y + TARGET_DIAMETER / 2 + 0.5
                );
    } else {
        destination.x =
                (rand() % 100) *
                (quadrantBounds[3][1] - quadrantBounds[3][0] - TARGET_DIAMETER) / 100.0 +
                quadrantBounds[3][0] + TARGET_DIAMETER;
        destination.y =
                (rand() % 100) *
                (quadrantBounds[3][3] - quadrantBounds[3][2] - TARGET_DIAMETER) / 100.0 +
                quadrantBounds[3][2] + TARGET_DIAMETER;
        obstacles[2].location.x =
                (rand() % 100) *
                (quadrantBounds[2][1] - quadrantBounds[2][0] - obstacles[2].width) / 100.0 +
                quadrantBounds[2][0];
        obstacles[2].location.y = min(
                (rand() % 100) *
                (quadrantBounds[2][3] - quadrantBounds[2][2] - obstacles[2].length) / 100.0 +
                quadrantBounds[2][2] + obstacles[2].length,
                destination.y - TARGET_DIAMETER / 2 - 0.5
                );
    }

    osv->startingLocation = startingLocation;
}

inline float Arena::max(float a, float b) {
    return a > b ? a : b;
}

inline float Arena::min(float a, float b) {
    return a < b ? a : b;
}
