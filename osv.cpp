#include "osv.h"

OSV::OSV(QObject *parent) : QObject(parent)
{
    location.x = 0.5;
    location.y = 1.0;
    location.theta = 0.0;
    destination.x = 0.0;
    destination.y = 0.0;

    width = DEFAULT_OSV_WIDTH;
    length = DEFAULT_OSV_LENGTH;
    location.theta = 0;
    leftPWM = 0;
    rightPWM = 0;
    prevLeftPWM = 0;
    prevRightPWM = 0;

    int widthPx = 229;
    int lengthPx = 239;

    QPen pen(Qt::green);
    pen.setWidth(5);

//    QImage image(widthPx, lengthPx, QImage::Format_ARGB32);
    QImage image(lengthPx, widthPx, QImage::Format_ARGB32);

    image.fill(qRgba(0, 0, 0, 0));
    QPainter paint;
    paint.begin(&image);
    paint.setPen(pen);

    //draw treads
    int treadWidth = 28;
    paint.fillRect(0, 0, lengthPx, treadWidth, treadColor);
    paint.fillRect(0, widthPx - treadWidth, lengthPx, treadWidth, treadColor);

    //draw body
    paint.fillRect(20, 50, lengthPx - 40, widthPx - 100, Qt::black);

    //draw aruco marker
    const int marker_top_x = lengthPx / 2 - MARKER_WIDTH / 2;
    const int marker_top_y = widthPx / 2 - MARKER_WIDTH / 2;
    paint.fillRect(lengthPx / 2 - WOOD_WIDTH / 2, widthPx / 2 - WOOD_WIDTH / 2, WOOD_WIDTH, WOOD_WIDTH, Qt::white);
    paint.fillRect(marker_top_x, marker_top_y, MARKER_WIDTH, MARKER_WIDTH, Qt::black);

    //marker #4
    int square_width = MARKER_WIDTH / 6;
    paint.fillRect(marker_top_x + 2*square_width, marker_top_y + square_width, square_width, 2*square_width, Qt::white);
    paint.fillRect(marker_top_x + 4*square_width, marker_top_y + square_width, square_width, square_width, Qt::white);
    paint.fillRect(marker_top_x + square_width, marker_top_y + 3*square_width, square_width, 2*square_width, Qt::white);
    paint.fillRect(marker_top_x + square_width, marker_top_y + 4*square_width, 3*square_width, square_width, Qt::white);
    paint.fillRect(marker_top_x + 4*square_width, marker_top_y + 3*square_width, square_width, square_width, Qt::white);



    //draw arrow
    paint.drawLine(marker_top_x, marker_top_y, marker_top_x + MARKER_WIDTH, marker_top_y);
    paint.drawLine(marker_top_x + MARKER_WIDTH, marker_top_y, marker_top_x + MARKER_WIDTH - 25, marker_top_y - 25);
    paint.drawLine(marker_top_x + MARKER_WIDTH, marker_top_y, marker_top_x + MARKER_WIDTH - 25, marker_top_y + 25);

    osvImage = image;

    for(int i = 0; i < 12; i++) {
        sensors[i] = false;
    }
    rand_eng.seed(gen.generate());

    readSettings();

}

void OSV::readSettings()
{
    QSettings settings("UMD ENES100", "Simulator");
    settings.beginGroup("OSVSettings");
    for (int i=0; i<12; i++) {
        QString name = "sensor" + QString::number(i);
        sensors[i] = settings.value(name, QVariant(false)).toBool();
    }
    this->length = settings.value("osv length", QVariant(DEFAULT_OSV_LENGTH)).toDouble();
    this->width = settings.value("osv width", QVariant(DEFAULT_OSV_WIDTH)).toDouble();
    settings.endGroup();
}

void OSV::writeSettings()
{
    QSettings settings("UMD ENES100", "Simulator");
    settings.beginGroup("OSVSettings");
    for (int i=0; i<12; i++) {
        QString name = "sensor" + QString::number(i);
        settings.setValue(name, sensors[i]);
    }
    settings.setValue("osv length", this->length);
    settings.setValue("osv width", this->width);
    settings.endGroup();
}

QImage OSV::draw()
{
    int widthPx = static_cast<int>(width * ppm);
    int lengthPx = static_cast<int>(length * ppm);

    QImage scaled = osvImage.scaled(lengthPx, widthPx);
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

    double avgPWM = (rightPWM + leftPWM) / 2;
    double speed = TANK_SPEED * (avgPWM) / (255.0 * 50.0);
    location.x = location.x + speed * cos(location.theta);
    location.y = location.y + speed * sin(location.theta);

    location.theta += 2 * PI * ROTATIONS_PER_SECOND / 50 * (rightPWM - leftPWM) / 255.0;


}

void OSV::setLeftPWM(int pwm, bool entropy)
{
    if (pwm == prevLeftPWM) {
        //prevent repeated calls from resetting pwm to avoid averaging of randomness
        return;
    }
    prevLeftPWM = pwm;
    double entropy_stddev = entropy ? ENTROPY_STDDEV : 0.0;
    std::normal_distribution<double> entropy_dist (pwm, pwm * entropy_stddev);
    leftPWM = static_cast<int>(entropy_dist(gen));
    leftPWM = MAX(-255,MIN(255, leftPWM));
}

void OSV::setRightPWM(int pwm, bool entropy)
{
    if (pwm == prevRightPWM) {
        //prevent repeated calls from resetting pwm to avoid averaging of randomness
        return;
    }
    prevRightPWM = pwm;
    double entropy_stddev = entropy ? 0.1 : 0.0;
    std::normal_distribution<double> entropy_dist (pwm,pwm * entropy_stddev);
    rightPWM = static_cast<int>(entropy_dist(gen));
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
