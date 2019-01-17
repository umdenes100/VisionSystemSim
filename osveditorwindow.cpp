#include "osveditorwindow.h"
#include "ui_osveditorwindow.h"

OSVEditorWindow::OSVEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSVEditorWindow)
{
    ui->setupUi(this);

}

void OSVEditorWindow::init(OSV *osv)
{
    this->osv = osv;
    EditorButton* widgetList [] = {ui->widget, ui->widget_2, ui->widget_3, ui->widget_4, ui->widget_5,ui->widget_6,
                                   ui->widget_7, ui->widget_8, ui->widget_9, ui->widget_10, ui->widget_11, ui->widget_12};

    for (int i=0; i<12; i++) {
        widgetList[i]->setIndex(i);
        connect(widgetList[i], SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
        if (osv->sensors[i]) {
            widgetList[i]->setState(2);
        } else {
            widgetList[i]->setState(0);
        }
    }

    ui->osvWidthSlider->setValue(static_cast<int>((osv->width - OSV_MIN_DIMENSION_METERS) * 99.0 / (OSV_MAX_DIMENSION_METERS - OSV_MIN_DIMENSION_METERS)));
    ui->osvLengthSlider->setValue(static_cast<int>((osv->length - OSV_MIN_DIMENSION_METERS) * 99.0 / (OSV_MAX_DIMENSION_METERS - OSV_MIN_DIMENSION_METERS)));
    ui->widthLabel->setText("Width: " + QString::number(static_cast<int>(osv->width * 1000)) + "mm");
    ui->lengthLabel->setText("Length: " + QString::number(static_cast<int>(osv->length * 1000)) + "mm");
}

OSVEditorWindow::~OSVEditorWindow()
{
    delete ui;
}

void OSVEditorWindow::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);

    QPen pen(Qt::darkGray);
    pen.setWidth(5);
    paint.setPen(pen);

    QPainter painter(this);

    painter.drawImage((this->width() - osv->osvImage.width()) / 2, (this->height() - osv->osvImage.height()) / 2, osv->osvImage);

    QPen pen2(Qt::black);
    pen2.setWidth(5);
    paint.setPen(pen2);
}

void OSVEditorWindow::buttonPressed(int index)
{
    osv->toggleSensor(index);
}

void OSVEditorWindow::on_osvLengthSlider_valueChanged(int value)
{
    osv->length = OSV_MIN_DIMENSION_METERS + ((OSV_MAX_DIMENSION_METERS - OSV_MIN_DIMENSION_METERS) * value / 99.0);
    ui->lengthLabel->setText("Length: " + QString::number(static_cast<int>(osv->length * 1000)) + "mm");
}

void OSVEditorWindow::on_osvWidthSlider_valueChanged(int value)
{
    osv->width = OSV_MIN_DIMENSION_METERS + ((OSV_MAX_DIMENSION_METERS - OSV_MIN_DIMENSION_METERS) * value / 99.0);
    ui->widthLabel->setText("Width: " + QString::number(static_cast<int>(osv->width * 1000)) + "mm");
}
