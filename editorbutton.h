#ifndef EDITORBUTTON_H
#define EDITORBUTTON_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

namespace Ui {
class EditorButton;
}

class EditorButton : public QWidget
{
    Q_OBJECT

public:
    explicit EditorButton(QWidget *parent = 0);
    ~EditorButton();

private:
    Ui::EditorButton *ui;
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    int buttonState = 0;
    int index;
};

#endif // EDITORBUTTON_H
