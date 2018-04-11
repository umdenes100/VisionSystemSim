#include "osveditorwindow.h"
#include "ui_osveditorwindow.h"

OSVEditorWindow::OSVEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSVEditorWindow)
{
    ui->setupUi(this);
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

void OSVEditorWindow::on_pushButton_clicked()
{
    osv->toggleSensor(0);
}

void OSVEditorWindow::on_pushButton_10_clicked()
{
    osv->toggleSensor(9);
}

void OSVEditorWindow::on_pushButton_11_clicked()
{
    osv->toggleSensor(10);
}

void OSVEditorWindow::on_pushButton_12_clicked()
{
    osv->toggleSensor(11);
}

void OSVEditorWindow::on_pushButton_2_clicked()
{
    osv->toggleSensor(1);
}

void OSVEditorWindow::on_pushButton_3_clicked()
{
    osv->toggleSensor(2);
}

void OSVEditorWindow::on_pushButton_4_clicked()
{
    osv->toggleSensor(3);
}

void OSVEditorWindow::on_pushButton_5_clicked()
{
    osv->toggleSensor(4);
}

void OSVEditorWindow::on_pushButton_6_clicked()
{
    osv->toggleSensor(5);
}

void OSVEditorWindow::on_pushButton_7_clicked()
{
    osv->toggleSensor(6);
}

void OSVEditorWindow::on_pushButton_8_clicked()
{
    osv->toggleSensor(7);
}

void OSVEditorWindow::on_pushButton_9_clicked()
{
    osv->toggleSensor(8);
}
