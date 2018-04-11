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
    OSV *osv;
    ~OSVEditorWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::OSVEditorWindow *ui;
    void paintEvent(QPaintEvent *e);
};

#endif // OSVEDITORWINDOW_H
