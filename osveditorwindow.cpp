#include "osveditorwindow.h"
#include "ui_osveditorwindow.h"

OSVEditorWindow::OSVEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSVEditorWindow)
{
    ui->setupUi(this);
    ui->widget->setIndex(0);
    connect(ui->widget, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    ui->widget_2->setIndex(1);
    connect(ui->widget_2, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    ui->widget_3->setIndex(2);
    connect(ui->widget_3, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    ui->widget_4->setIndex(3);
    connect(ui->widget_4, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    ui->widget_5->setIndex(4);
    connect(ui->widget_5, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    ui->widget_6->setIndex(5);
    connect(ui->widget_6, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    ui->widget_7->setIndex(6);
    connect(ui->widget_7, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    ui->widget_8->setIndex(7);
    connect(ui->widget_8, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    ui->widget_9->setIndex(8);
    connect(ui->widget_9, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    ui->widget_10->setIndex(9);
    connect(ui->widget_10, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    ui->widget_11->setIndex(10);
    connect(ui->widget_11, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
    ui->widget_12->setIndex(11);
    connect(ui->widget_12, SIGNAL(pressed(int)), this, SLOT(buttonPressed(int)));
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

    int widthPx = 229;
    int heightPx = 239;

    paint.translate(width() / 2 - widthPx / 2, height() / 2 - heightPx / 2);


    paint.fillRect(0, 0, widthPx, 28, QColor(80,80,80));
    paint.fillRect(0, heightPx - 28, widthPx, 28, QColor(80,80,80));
    QPen pen2(Qt::black);
    pen2.setWidth(5);
    paint.setPen(pen2);
    paint.fillRect(20, 50, widthPx - 40, heightPx - 100, Qt::black);
}

void OSVEditorWindow::buttonPressed(int index)
{
    osv->toggleSensor(index);
}
