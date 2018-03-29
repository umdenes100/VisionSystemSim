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
