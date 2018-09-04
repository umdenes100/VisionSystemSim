#include "osveditorwindow.h"
#include "ui_osveditorwindow.h"
#include <QPainter>

OSVEditorWindow::OSVEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSVEditorWindow)
{
    ui->setupUi(this);
}

void OSVEditorWindow::init(OSV *osv)
{
    this->osv = osv;
    ui->widget->setIndex(0);
    connect(ui->widget, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[0]) {
        ui->widget->setState(2);
    } else {
        ui->widget->setState(0);
    }
    ui->widget_2->setIndex(1);
    connect(ui->widget_2, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[1]) {
        ui->widget_2->setState(2);
    } else {
        ui->widget_2->setState(0);
    }
    ui->widget_3->setIndex(2);
    connect(ui->widget_3, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[2]) {
        ui->widget_3->setState(2);
    } else {
        ui->widget_3->setState(0);
    }
    ui->widget_4->setIndex(3);
    connect(ui->widget_4, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[3]) {
        ui->widget_4->setState(2);
    } else {
        ui->widget_4->setState(0);
    }
    ui->widget_5->setIndex(4);
    connect(ui->widget_5, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[4]) {
        ui->widget_5->setState(2);
    } else {
        ui->widget_5->setState(0);
    }
    ui->widget_6->setIndex(5);
    connect(ui->widget_6, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[5]) {
        ui->widget_6->setState(2);
    } else {
        ui->widget_6->setState(0);
    }
    ui->widget_7->setIndex(6);
    connect(ui->widget_7, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[6]) {
        ui->widget_7->setState(2);
    } else {
        ui->widget_7->setState(0);
    }
    ui->widget_8->setIndex(7);
    connect(ui->widget_8, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[7]) {
        ui->widget_8->setState(2);
    } else {
        ui->widget_8->setState(0);
    }
    ui->widget_9->setIndex(8);
    connect(ui->widget_9, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[8]) {
        ui->widget_9->setState(2);
    } else {
        ui->widget_9->setState(0);
    }
    ui->widget_10->setIndex(9);
    connect(ui->widget_10, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[9]) {
        ui->widget_10->setState(2);
    } else {
        ui->widget_10->setState(0);
    }
    ui->widget_11->setIndex(10);
    connect(ui->widget_11, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[10]) {
        ui->widget_11->setState(2);
    } else {
        ui->widget_11->setState(0);
    }
    ui->widget_12->setIndex(11);
    connect(ui->widget_12, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    if(osv->sensors[11]) {
        ui->widget_12->setState(2);
    } else {
        ui->widget_12->setState(0);
    }
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
