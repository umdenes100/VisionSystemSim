#ifndef OSVEDITORWINDOW_H
#define OSVEDITORWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "detail.h"
#include "osv.h"

namespace Ui {
class OSVEditorWindow;
}

class OSVEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OSVEditorWindow(QWidget *parent = nullptr);
    void init(OSV* osv);
    OSV *osv;
    ~OSVEditorWindow();

public slots:
    void buttonPressed(int index);

private slots:
    void on_osvLengthSlider_valueChanged(int value);
    void on_osvWidthSlider_valueChanged(int value);

private:
    Ui::OSVEditorWindow *ui;
    void paintEvent(QPaintEvent *e);
};

#endif // OSVEDITORWINDOW_H
