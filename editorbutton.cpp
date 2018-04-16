#include "editorbutton.h"
#include "ui_editorbutton.h"

EditorButton::EditorButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorButton)
{
    ui->setupUi(this);
    setMouseTracking(true);
}

EditorButton::~EditorButton()
{
    delete ui;
}

void EditorButton::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    QPen pen(Qt::black);
    pen.setWidth(3);
    QPen whitePen(Qt::white);
    whitePen.setWidth(3);
    paint.setPen(pen);
    QFont font("default", 12);
    paint.setFont(font);
    QFontMetrics metrics(font);

    switch(buttonState) {
    case 0:
        paint.drawRect(0, 0, this->width() - 1, this->height() - 1);
        break;
    case 1:
        paint.fillRect(0, 0, this->width() - 1, this->height() - 1, QColor(200, 200, 200));
        paint.drawRect(0, 0, this->width() - 1, this->height() - 1);
        break;
    case 2:
        paint.fillRect(0, 0, this->width() - 1, this->height() - 1, QColor(75, 75, 75));
        paint.drawRect(0, 0, this->width() - 1, this->height() - 1);
        paint.setPen(whitePen);
        paint.drawText(QPoint(width() / 2 - (metrics.width(QString::number(index)) / 2), height() / 2 + 8), QString::number(index));
        paint.setPen(pen);
        break;
    }
}

void EditorButton::enterEvent(QEvent *e)
{
    if(buttonState != 2) {
        buttonState = 1;
        update();
    }
}

void EditorButton::leaveEvent(QEvent *e)
{
    if(buttonState != 2) {
        buttonState = 0;
        update();
    }
}

void EditorButton::mousePressEvent(QMouseEvent *e)
{
    if(buttonState == 2) {
        buttonState = 1;
    } else {
        buttonState = 2;
    }

    update();
}

void EditorButton::setIndex(int index)
{
    this->index = index;
}
