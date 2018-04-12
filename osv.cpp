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

    int widthPx = 229;
    int heightPx = 239;

    QImage image(widthPx, heightPx, QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));
    QPainter paint;
    QPen pen(Qt::darkGray);
    pen.setWidth(5);
    paint.begin(&image);
    paint.setPen(pen);

    paint.fillRect(0, 0, widthPx, 28, QColor(80,80,80));
    paint.fillRect(0, heightPx - 28, widthPx, 28, QColor(80,80,80));
    QPen pen2(Qt::black);
    pen2.setWidth(5);
    paint.setPen(pen2);
    paint.fillRect(20, 50, widthPx - 40, heightPx - 100, Qt::black);

    osvImage = image;
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

    if(location.theta > 2 * PI) {
        location.theta -= 2 * PI;
    }

    float speed = ((TANK_SPEED * ((rightPWM + leftPWM) / 2)) / 255.0) / 50.0;
    location.x = location.x + speed * cos(location.theta);
    location.y = location.y + speed * sin(location.theta);


    location.theta += 2 * PI * ROTATIONS_PER_SECOND / 50 * (float)(rightPWM - leftPWM) / 255.0;


}

void OSV::setLeftPWM(int pwm)
{
    leftPWM = pwm;
}

void OSV::setRightPWM(int pwm)
{
    rightPWM = pwm;
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
