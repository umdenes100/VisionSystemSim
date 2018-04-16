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
    void setHorizontal();
    ~EditorButton();

private:
    Ui::EditorButton *ui;
    void paintEvent(QPaintEvent *e);
};

#endif // EDITORBUTTON_H
