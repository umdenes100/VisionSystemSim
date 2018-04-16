#include "editorbutton.h"
#include "ui_editorbutton.h"

EditorButton::EditorButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorButton)
{
    ui->setupUi(this);
}

EditorButton::~EditorButton()
{
    delete ui;
}

void EditorButton::setHorizontal()
{

}

void EditorButton::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    QPen pen(Qt::black);
    pen.setWidth(3);
    paint.setPen(pen);

    paint.drawRect(0, 0, this->width() - 1, this->height() - 1);
}
