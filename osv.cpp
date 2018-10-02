#include <math.h>
#include "osv.h"

OSV::OSV(QObject *parent) : QObject(parent)
{
    location.x = 0.5;
    location.y = 1;
    location.theta = 0;
    destination.x = 0.0;
    destination.y = 0.0;

    width = 0.229;
    length = 0.239;
    location.theta = 0;
    leftPWM = rightPWM = 0;

    const int widthPx = 229;
    const int heightPx = 239;

    QPen pen(Qt::green);
    pen.setWidth(5);

    QImage image(widthPx, heightPx, QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));
    QPainter paint;
    paint.begin(&image);
    paint.setPen(pen);

    //draw treads
    paint.fillRect(0, 0, widthPx, 28, QColor(80,80,80));
    paint.fillRect(0, heightPx - 28, widthPx, 28, QColor(80,80,80));

    //draw body
    paint.fillRect(20, 50, widthPx - 40, heightPx - 100, Qt::black);

    //draw aruco marker
    const int marker_top_x = widthPx / 2 - MARKER_WIDTH / 2;
    const int marker_top_y = heightPx / 2 - MARKER_WIDTH / 2;
    paint.fillRect(widthPx / 2 - WOOD_WIDTH / 2, heightPx / 2 - WOOD_WIDTH / 2, WOOD_WIDTH, WOOD_WIDTH, Qt::white);
    paint.fillRect(marker_top_x, marker_top_y, MARKER_WIDTH, MARKER_WIDTH, Qt::black);

    //marker #121
    int square_width = MARKER_WIDTH / 7;
    paint.fillRect(marker_top_x + square_width, marker_top_y + square_width, square_width, 2*square_width, Qt::white);
    paint.fillRect(marker_top_x + square_width, marker_top_y + 5*square_width, square_width, square_width, Qt::white);
    paint.fillRect(marker_top_x + 2*square_width, marker_top_y + 3*square_width, square_width, 2*square_width, Qt::white);
    paint.fillRect(marker_top_x + 3*square_width, marker_top_y + 2*square_width, 2*square_width, 2*square_width, Qt::white);
    paint.fillRect(marker_top_x + 3*square_width, marker_top_y + 5*square_width, 3*square_width, square_width, Qt::white);
    paint.fillRect(marker_top_x + 5*square_width, marker_top_y + 4*square_width, square_width, square_width, Qt::white);
    paint.fillRect(marker_top_x + 5*square_width, marker_top_y + 2*square_width, square_width, square_width, Qt::white);


    //draw arrow
    paint.drawLine(marker_top_x, marker_top_y, marker_top_x + MARKER_WIDTH, marker_top_y);
    paint.drawLine(marker_top_x + MARKER_WIDTH, marker_top_y, marker_top_x + MARKER_WIDTH - 25, marker_top_y - 25);
    paint.drawLine(marker_top_x + MARKER_WIDTH, marker_top_y, marker_top_x + MARKER_WIDTH - 25, marker_top_y + 25);

    osvImage = image;

    for(int i = 0; i < 12; i++) {
        sensors[i] = false;
    }
}

QImage OSV::draw()
{
    int widthPx = width * ppm;
    int heightPx = length * ppm;

    QImage scaled = osvImage.scaled(widthPx, heightPx);
    QPoint center = scaled.rect().center();
    QMatrix matrix;
    matrix.translate(center.x(), center.y());
    matrix.rotate(-location.theta * 180 / PI);
    QImage dstImg = scaled.transformed(matrix);

    return dstImg;
}

void OSV::refreshLocation()
{
    if(abs(leftPWM) > 255 || abs(rightPWM) > 255) {
        return;
    }

    prevLocation.x = location.x;
    prevLocation.y = location.y;
    prevLocation.theta = location.theta;

    if(location.theta > PI) {
        location.theta -= 2 * PI;
    }

    if(location.theta < - PI) {
        location.theta += 2 * PI;
    }

    float speed = ((TANK_SPEED * ((rightPWM + leftPWM) / 2)) / 255.0) / 50.0;
    location.x = location.x + speed * cos(location.theta);
    location.y = location.y + speed * sin(location.theta);


    location.theta += 2 * PI * ROTATIONS_PER_SECOND / 50 * (float)(rightPWM - leftPWM) / 255.0;


}

void OSV::setLeftPWM(int pwm, int entropy)
{
    if (pwm == 0) {
        leftPWM = 0;
        return;
    }
    time_t t;
    srand((unsigned) time(&t));
    std::normal_distribution<double> entropy_dist (pwm, pwm * entropy / (255 * 5));
    std::default_random_engine gen;
    gen.seed(rand());
    leftPWM = entropy_dist(gen);
    leftPWM = MAX(-255,MIN(255, leftPWM));
}

void OSV::setRightPWM(int pwm, int entropy)
{
    if (pwm == 0) {
        rightPWM = 0;
        return;
    }
    time_t t;
    srand((unsigned) time(&t));
    std::normal_distribution<double> entropy_dist (pwm,pwm * entropy / (255 * 5));
    std::default_random_engine gen;
    gen.seed(rand());
    rightPWM = entropy_dist(gen);
    rightPWM = MAX(-255, MIN(255,rightPWM));
}

void OSV::toggleSensor(int index)
{
    if (sensors[index] == false)
        sensors[index] = true;
    else
        sensors[index] = false;
}

void OSV::setLocation(Point p)
{
    this->location = p;
    this->location.theta = p.theta;
}
