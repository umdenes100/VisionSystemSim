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
    customCoordinate.x = 0;
    customCoordinate.y = 0;
}

Arena::~Arena()
{
    delete ui;
}

void Arena::customButtonClicked(int arg1)
{
    this->customShowing = (arg1 == 2);
}

void Arena::refresh()
{
    osv->refreshLocation();


    // we have to get the slope of the front side of the osv first
    Point midPoint;
    midPoint.x = osv->location.x + osv->width / 2 * cos(osv->location.theta);
    midPoint.y = osv->location.y + osv->width / 2 * sin(osv->location.theta);

    Point a;
    a.x = midPoint.x - osv->length / 2 * sin(osv->location.theta);
    a.y = midPoint.y + osv->length / 2 * cos(osv->location.theta);

    Point b;
    b.x = midPoint.x + osv->length / 2 * sin(osv->location.theta);
    b.y = midPoint.y - osv->length / 2 * cos(osv->location.theta);

    Point midPoint2;
    midPoint2.x = osv->location.x - osv->width / 2 * cos(osv->location.theta);
    midPoint2.y = osv->location.y - osv->width / 2 * sin(osv->location.theta);

    Point c;
    c.x = midPoint2.x - osv->length / 2 * sin(osv->location.theta);
    c.y = midPoint2.y + osv->length / 2 * cos(osv->location.theta);

    Point d;
    d.x = midPoint2.x + osv->length / 2 * sin(osv->location.theta);
    d.y = midPoint2.y - osv->length / 2 * cos(osv->location.theta);

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
        osv->location.theta = osv->prevLocation.theta;
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

    if(customShowing) {
        paint.drawEllipse(metersToPixels(customCoordinate), metersToPixels(TARGET_DIAMETER / 2), metersToPixels(TARGET_DIAMETER / 2));
    }
}

void Arena::customCoordinateChanged(float value, bool isX)
{
    if(isX) {
        customCoordinate.x = value;
    } else {
        customCoordinate.y = value;
    }
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
    time_t t;
    srand((unsigned) time(&t));

    osv->setLeftPWM(0);
    osv->setRightPWM(0);

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
    osv->setLocation(startingLocation);

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
    osv->destination = destination;
}

void Arena::reset()
{
    osv->setLeftPWM(0);
    osv->setRightPWM(0);
    osv->setLocation(startingLocation);
}

float Arena::getDistance(int index)
{

    if(!osv->sensors[index]) {
        return 0;
    }

    // we have to get the slope of the front side of the osv first
    Point midPointFront;
    midPointFront.x = osv->location.x + osv->width / 2 * cos(osv->location.theta);
    midPointFront.y = osv->location.y + osv->width / 2 * sin(osv->location.theta);

    Point a;
    a.x = midPointFront.x - osv->length / 2 * sin(osv->location.theta);
    a.y = midPointFront.y + osv->length / 2 * cos(osv->location.theta);

    Point b;
    b.x = midPointFront.x + osv->length / 2 * sin(osv->location.theta);
    b.y = midPointFront.y - osv->length / 2 * cos(osv->location.theta);

    Point midPointBack;
    midPointBack.x = osv->location.x - osv->width / 2 * cos(osv->location.theta);
    midPointBack.y = osv->location.y - osv->width / 2 * sin(osv->location.theta);

    Point c;
    c.x = midPointBack.x - osv->length / 2 * sin(osv->location.theta);
    c.y = midPointBack.y + osv->length / 2 * cos(osv->location.theta);

    Point d;
    d.x = midPointBack.x + osv->length / 2 * sin(osv->location.theta);
    d.y = midPointBack.y - osv->length / 2 * cos(osv->location.theta);

    Point midPointLeft;
    midPointLeft.x = (a.x + c.x) / 2;
    midPointLeft.y = (a.y + c.y) / 2;

    Point midPointRight;
    midPointRight.x = (b.x + d.x) / 2;
    midPointRight.y = (b.y + d.y) / 2;

    Point sensorLocations[12] {a, midPointFront, b, b, midPointRight, d, d, midPointBack, c, c, midPointLeft, a};

    int sideIndex = index / 3;
    float orientation = osv->location.theta + sideIndex * PI / 2;

    int range = 1;
    Point endPoint;
    endPoint.x = sensorLocations[index].x + range * cos(orientation);
    endPoint.y = sensorLocations[index].y + range * sin(orientation);

    QLineF sensorTrace(sensorLocations[index].x, sensorLocations[index].y, endPoint.x, endPoint.y);
    float minimumDistance = 1;
    QPointF *tempPoint = new QPointF(0,0);

    for(int i = 0; i < 3; i++) {
        // for each of the obstacles
        QLineF right(obstacles[i].location.x + obstacles[i].width, obstacles[i].location.y, obstacles[i].location.x + obstacles[i].width, obstacles[i].location.y - obstacles[i].length);
        QLineF bottom(obstacles[i].location.x, obstacles[i].location.y - obstacles[i].length, obstacles[i].location.x + obstacles[i].width, obstacles[i].location.y - obstacles[i].length);
        QLineF left(obstacles[i].location.x, obstacles[i].location.y - obstacles[i].length, obstacles[i].location.x, obstacles[i].location.y);
        QLineF top(obstacles[i].location.x, obstacles[i].location.y, obstacles[i].location.x + obstacles[i].width, obstacles[i].location.y);

        if(right.intersect(sensorTrace, tempPoint) == QLineF::BoundedIntersection) {
            float tempDistance = distance(sensorLocations[index], tempPoint);
            if(tempDistance < minimumDistance) {
                minimumDistance = tempDistance;
            }
        }

        if(left.intersect(sensorTrace, tempPoint) == QLineF::BoundedIntersection) {
            float tempDistance = distance(sensorLocations[index], tempPoint);
            if(tempDistance < minimumDistance) {
                minimumDistance = tempDistance;
            }
        }

        if(top.intersect(sensorTrace, tempPoint) == QLineF::BoundedIntersection) {
            float tempDistance = distance(sensorLocations[index], tempPoint);
            if(tempDistance < minimumDistance) {
                minimumDistance = tempDistance;
            }
        }

        if(bottom.intersect(sensorTrace, tempPoint) == QLineF::BoundedIntersection) {
            float tempDistance = distance(sensorLocations[index], tempPoint);
            if(tempDistance < minimumDistance) {
                minimumDistance = tempDistance;
            }
        }
    }

    return minimumDistance;
}

inline float Arena::max(float a, float b) {
    return a > b ? a : b;
}

inline float Arena::min(float a, float b) {
    return a < b ? a : b;
}

inline float Arena::distance(Point a, QPointF *b) {
    return sqrt(pow(a.x - b->x(), 2) + pow(a.y - b->y(), 2));
}
