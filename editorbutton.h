#ifndef EDITORBUTTON_H
#define EDITORBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QFont>
#include <QFontMetrics>

namespace Ui {
class EditorButton;
}

class EditorButton : public QWidget
{
    Q_OBJECT

public:
    explicit EditorButton(QWidget *parent = 0);
    void setIndex(int index);
    void setState(int state);
    ~EditorButton();

signals:
    void pressed(int index);

private:
    Ui::EditorButton *ui;
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    int buttonState;
    int index;
};

#endif // EDITORBUTTON_H
