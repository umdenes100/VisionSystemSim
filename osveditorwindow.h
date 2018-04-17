#ifndef OSVEDITORWINDOW_H
#define OSVEDITORWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "osv.h"

namespace Ui {
class OSVEditorWindow;
}

class OSVEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OSVEditorWindow(QWidget *parent = 0);
    void init(OSV* osv);
    OSV *osv;
    ~OSVEditorWindow();

public slots:
    void buttonPressed(int index);

private:
    Ui::OSVEditorWindow *ui;
    void paintEvent(QPaintEvent *e);
};

#endif // OSVEDITORWINDOW_H
