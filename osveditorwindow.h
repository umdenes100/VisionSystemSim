#ifndef OSVEDITORWINDOW_H
#define OSVEDITORWINDOW_H

#include <QMainWindow>
#include <QPainter>

namespace Ui {
class OSVEditorWindow;
}

class OSVEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OSVEditorWindow(QWidget *parent = 0);
    ~OSVEditorWindow();

private:
    Ui::OSVEditorWindow *ui;
    void paintEvent(QPaintEvent *e);
};

#endif // OSVEDITORWINDOW_H
