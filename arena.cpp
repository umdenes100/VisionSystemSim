#include "arena.h"
#include "ui_arena.h"

Arena::Arena(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Arena)
{
    setMouseTracking(true);
    timeElapsed = QTime::currentTime();
    osv = new OSV();
    randomize();
    ui->setupUi(this);
    refreshTimer = new QTimer();
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(timerTick()));
    refreshTimer->start(3);
    readSettings();
}

Arena::~Arena()
{
    delete ui;
}

void Arena::writeSettings()
{
    QSettings settings("UMD ENES100", "Simulator");
    settings.beginGroup("Arena");
    settings.setValue("entropy", entropyEnabled);
    settings.setValue("obstacles", obstaclesEnabled);
    settings.endGroup();
}

void Arena::readSettings()
{
    QSettings settings("UMD ENES100", "Simulator");
    settings.beginGroup("Arena");
    entropyEnabled = settings.value("entropy", QVariant(false)).toBool();
    obstaclesEnabled = settings.value("obstacles", QVariant(true)).toBool();
    settings.endGroup();
}

void Arena::timerTick()
{
    if(timeElapsed.elapsed() > 30) {
        timeElapsed = QTime::currentTime();
        refresh();
    }
}

void Arena::refresh()
{
    osv->refreshLocation();

    if(checkForCollisions()) {
        osv->location.x = osv->prevLocation.x;
        osv->location.y = osv->prevLocation.y;
        osv->location.theta = osv->prevLocation.theta;
    }

    update();
}

bool Arena::checkForCollisions()
{
    // points a,b,c,d represent the four corners of the OSV
    double cos_theta = cos(osv->location.theta);
    double sin_theta = sin(osv->location.theta);
    Point midPointFront;
    midPointFront.x = osv->location.x + osv->length / 2 * cos_theta;
    midPointFront.y = osv->location.y + osv->length / 2 * sin_theta;

    Point a;
    a.x = midPointFront.x - osv->width / 2 * sin_theta;
    a.y = midPointFront.y + osv->width / 2 * cos_theta;

    Point b;
    b.x = midPointFront.x + osv->width / 2 * sin_theta;
    b.y = midPointFront.y - osv->width / 2 * cos_theta;

    Point midPointBack;
    midPointBack.x = osv->location.x - osv->length / 2 * cos_theta;
    midPointBack.y = osv->location.y - osv->length / 2 * sin_theta;

    Point c;
    c.x = midPointBack.x - osv->width / 2 * sin_theta;
    c.y = midPointBack.y + osv->width / 2 * cos_theta;

    Point d;
    d.x = midPointBack.x + osv->width / 2 * sin_theta;
    d.y = midPointBack.y - osv->width / 2 * cos_theta;

    QLineF frontOSV(a.x, a.y, b.x, b.y);
    QLineF leftOSV(a.x, a.y, c.x, c.y);
    QLineF backOSV(c.x, c.y, d.x, d.y);
    QLineF rightOSV(b.x, b.y, d.x, d.y);
    QLineF osvSides [] = {frontOSV, leftOSV, backOSV, rightOSV};

    if (obstaclesEnabled) {
        for(Obstacle obstacle:obstacles) {
            // for each of the obstacles
            QLineF right(obstacle.location.x + obstacle.width, obstacle.location.y, obstacle.location.x + obstacle.width, obstacle.location.y - obstacle.length);
            QLineF bottom(obstacle.location.x, obstacle.location.y - obstacle.length, obstacle.location.x + obstacle.width, obstacle.location.y - obstacle.length);
            QLineF left(obstacle.location.x, obstacle.location.y - obstacle.length, obstacle.location.x, obstacle.location.y);
            QLineF top(obstacle.location.x, obstacle.location.y, obstacle.location.x + obstacle.width, obstacle.location.y);
            QLineF obstacleSides [] = {right, bottom, left, top};

            for(QLineF obstacleSide:obstacleSides) {
                for(QLineF osvSide : osvSides) {
                    if(obstacleSide.intersect(osvSide, nullptr) == QLineF::BoundedIntersection) {
                        return true;
                    }
                }

            }
        }
    }

    // now we want to define the walls:
    QLineF right(4.0, 0.0, 4.0, 2.0);
    QLineF bottom(0.0, 0.0, 4.0, 0.0);
    QLineF left(0.0, 0.0, 0.0, 2.0);
    QLineF top(0.0, 2.0, 4.0, 2.0);
    QLineF walls [] = {right, bottom, left, top};

    //need to check right and left sides of OSV in case OSV is perpendicular to wall
    for(QLineF wall: walls) {
        for(QLineF osvSide : osvSides) {
            if(wall.intersect(osvSide, nullptr) == QLineF::BoundedIntersection) {
                return true;
            }
        }
    }
    return false;
}

bool Arena::event(QEvent* event)
{
    if (event->type() == QEvent::ToolTip) {
        int areaWidth = 80;
        int destDiameterPx = metersToPixels(TARGET_DIAMETER);

        QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);
        QRect area = QRect(helpEvent->globalX() - areaWidth, helpEvent->globalY() - areaWidth, areaWidth, areaWidth);
        QRect terrain = QRect(metersToPixels(Point{0.65,0,0}).x(), metersToPixels(Point{0,1.995,0}).y(), metersToPixels(0.6), metersToPixels(1.992));
        QRect dest = QRect(metersToPixels(destination).x() - (destDiameterPx / 2), metersToPixels(destination).y() - (destDiameterPx / 2), destDiameterPx, destDiameterPx);

        if (terrain.contains(helpEvent->pos())) {
            QToolTip::showText(helpEvent->globalPos(), "rocky terrain", this, area, 2000);

        } else if (dest.contains(helpEvent->pos())){
            QString destinationTip = QString("destination: (") + QString::number(destination.x) + QString(",") + QString::number(destination.y) + QString(")") ;
            QToolTip::showText(helpEvent->globalPos(), destinationTip, this, area, 2000);

        } else {
            if (obstaclesEnabled) {
                QRect obstacle0 = QRect(metersToPixels(obstacles[0].location), QSize(metersToPixels(obstacles[0].width), metersToPixels(obstacles[0].length)));
                QRect obstacle1 = QRect(metersToPixels(obstacles[1].location), QSize(metersToPixels(obstacles[1].width), metersToPixels(obstacles[1].length)));
                QRect obstacle2 = QRect(metersToPixels(obstacles[2].location), QSize(metersToPixels(obstacles[2].width), metersToPixels(obstacles[2].length)));
                QRect obstacleRects [] = {obstacle0, obstacle1, obstacle2};

                for (QRect rect : obstacleRects) {
                    if (rect.contains(helpEvent->pos())) {
                        QToolTip::showText(helpEvent->globalPos(), "obstacle", this, area, 2000);
                    }
                }
            }
        }
        return true;
    }
    return QWidget::event(event);
}

void Arena::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    QPen pen(Qt::black);
    //QPen brownPen();

    pen.setWidth(2);
    paint.setPen(pen);

    // TODO: draw background

    if(static_cast<double>(width() + 2 * xOffsetPx) / static_cast<double>(height() + 2 * yOffsetPx) < 2) {
        arenaWidthPx = width() - 60;
        arenaHeightPx = arenaWidthPx / 2;

        xOffsetPx = 30;
        yOffsetPx = height() / 2 - arenaHeightPx / 2;
        paint.fillRect(xOffsetPx, yOffsetPx, arenaWidthPx, arenaHeightPx, sandColor);
        paint.drawRect(xOffsetPx, yOffsetPx, arenaWidthPx, arenaHeightPx);
    } else {
        arenaHeightPx = height() - 60;
        arenaWidthPx = arenaHeightPx * 2;

        yOffsetPx = 30;
        xOffsetPx = width() / 2 - arenaWidthPx / 2;
        paint.fillRect(xOffsetPx, yOffsetPx, arenaWidthPx, arenaHeightPx, sandColor);
        paint.drawRect(xOffsetPx, yOffsetPx, arenaWidthPx, arenaHeightPx);
    }

    osv->ppm = arenaWidthPx / 4.0;

    QImage osvImage = osv->draw();

    //draw terrain
    paint.fillRect(metersToPixels(Point{0.65,0,0}).x(), metersToPixels(Point{0,1.995,0}).y(), metersToPixels(0.6), metersToPixels(1.992), terrainColor);

    paint.drawImage(metersToPixels(osv->location) - osvImage.rect().center(), osvImage);
    if (obstaclesEnabled){
        for(int i = 0; i < 3; i++) {
            paint.fillRect(metersToPixels(obstacles[i].location).x(), metersToPixels(obstacles[i].location).y(), metersToPixels(obstacles[i].width), metersToPixels(obstacles[i].length), obstacleColor);
        }
    }

    paint.drawEllipse(metersToPixels(destination), metersToPixels(TARGET_DIAMETER / 2), metersToPixels(TARGET_DIAMETER / 2));

}

void Arena::entropyChanged(bool enabled)
{
    entropyEnabled = enabled;
}
void Arena::obstaclesToggled(bool enabled)
{
    obstaclesEnabled = enabled;
}

bool Arena::getEntropy()
{
    return entropyEnabled;
}

int Arena::metersToPixels(double length)
{
    return static_cast<int>(length * arenaWidthPx / 4.0);
}

QPoint Arena::metersToPixels(Point inMeters)
{
    QPoint inPixels;
    inPixels.setX(static_cast<int>(xOffsetPx + arenaWidthPx * (inMeters.x / 4.0)));
    inPixels.setY(static_cast<int>(yOffsetPx + arenaHeightPx - arenaHeightPx * (inMeters.y / 2.0)));

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
    osv->setLeftPWM(0);
    osv->setRightPWM(0);

    // Generate a random starting position
    startingLocation.x = 0.35;
    startingLocation.y = 0.4 + (rand() % 5) * 0.3;
    startingLocation.theta = (rand() % 4) * PI / 2 - PI;

    static const int presets[6][3] = {
           {0, 1, 2},
           {2, 1, 0},
           {0, 2, 1},
           {2, 0, 1},
           {1, 0, 2},
           {1, 2, 0}
       };

       const int randomization = rand() % 6;


       // Akhil's Algorithm

       for(int i = 0; i < 3; i++) {
           // y location is either 1.8, 1.25, or 0.7: distances of 0.65
           float baseY = presets[randomization][i] * 0.65 + OBSTACLE_HEIGHT + 0.1;
           obstacles[i].location.y = baseY;

           obstacles[i].location.x = i * 0.55 + 1.5;
           obstacles[i].length = OBSTACLE_HEIGHT;
           obstacles[i].width = OBSTACLE_WIDTH;
       }

       // the target randomization will be in a box
       float xMin = 2.8 + 0.4 + TARGET_DIAMETER / 2;
       float xMax = 4 - OSV_WIDTH - 0.1 - TARGET_DIAMETER / 2;
       float yMin = 0.4 + TARGET_DIAMETER / 2;
       float yMax = 2 - 0.4 - TARGET_DIAMETER / 2;

       // we now have ranges
       destination.x = (rand() % 100) / 100.0 * (xMax - xMin) + xMin;
       destination.y = (rand() % 100) / 100.0 * (yMax - yMin) + yMin;

    osv->startingLocation = startingLocation;
    osv->destination = destination;
    osv->setLocation(startingLocation);
}

void Arena::reset()
{
    osv->setLeftPWM(0);
    osv->setRightPWM(0);
    osv->setLocation(startingLocation);
}

double Arena::getDistance(int index)
{

    if(!osv->sensors[index]) {
        return 0;
    }

    // we have to get the slope of the front side of the osv first
    double cos_theta = cos(osv->location.theta);
    double sin_theta = sin(osv->location.theta);
    Point midPointFront;
    midPointFront.x = osv->location.x + osv->width / 2 * cos_theta;
    midPointFront.y = osv->location.y + osv->width / 2 * sin_theta;

    Point a;
    a.x = midPointFront.x - osv->length / 2 * sin_theta;
    a.y = midPointFront.y + osv->length / 2 * cos_theta;

    Point b;
    b.x = midPointFront.x + osv->length / 2 * sin_theta;
    b.y = midPointFront.y - osv->length / 2 * cos_theta;

    Point midPointBack;
    midPointBack.x = osv->location.x - osv->width / 2 * cos_theta;
    midPointBack.y = osv->location.y - osv->width / 2 * sin_theta;

    Point c;
    c.x = midPointBack.x - osv->length / 2 * sin_theta;
    c.y = midPointBack.y + osv->length / 2 * cos_theta;

    Point d;
    d.x = midPointBack.x + osv->length / 2 * sin_theta;
    d.y = midPointBack.y - osv->length / 2 * cos_theta;

    Point midPointLeft;
    midPointLeft.x = (a.x + c.x) / 2;
    midPointLeft.y = (a.y + c.y) / 2;

    Point midPointRight;
    midPointRight.x = (b.x + d.x) / 2;
    midPointRight.y = (b.y + d.y) / 2;

    Point sensorLocations[12] {a, midPointFront, b, b, midPointRight, d, d, midPointBack, c, c, midPointLeft, a};

    int sideIndex = index / 3;
    double orientation = osv->location.theta - sideIndex * PI / 2;

    double range = 1.0;
    Point endPoint;
    endPoint.x = sensorLocations[index].x + range * cos(orientation);
    endPoint.y = sensorLocations[index].y + range * sin(orientation);

    QLineF sensorTrace(sensorLocations[index].x, sensorLocations[index].y, endPoint.x, endPoint.y);
    double minimumDistance = 1.0;
    QPointF *tempPoint = new QPointF(0,0);
    if (obstaclesEnabled) {
        for(Obstacle obstacle:obstacles) {
            // for each of the obstacles
            QLineF right(obstacle.location.x + obstacle.width, obstacle.location.y, obstacle.location.x + obstacle.width, obstacle.location.y - obstacle.length);
            QLineF bottom(obstacle.location.x, obstacle.location.y - obstacle.length, obstacle.location.x + obstacle.width, obstacle.location.y - obstacle.length);
            QLineF left(obstacle.location.x, obstacle.location.y - obstacle.length, obstacle.location.x, obstacle.location.y);
            QLineF top(obstacle.location.x, obstacle.location.y, obstacle.location.x + obstacle.width, obstacle.location.y);
            QLineF obstacleSides [] = {right, bottom, left, top};

            for(QLineF obstacleSide : obstacleSides) {
                if(obstacleSide.intersect(sensorTrace, tempPoint) == QLineF::BoundedIntersection) {
                    minimumDistance = MIN(minimumDistance,distance(sensorLocations[index], tempPoint));
                }
            }
        }
    }

    return minimumDistance;
}

inline double Arena::distance(Point a, QPointF *b) {
    return (sqrt(pow(a.x - b->x(), 2) + pow(a.y - b->y(), 2)));
}
