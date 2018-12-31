#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtNetwork>
#include <QEventLoop>
#include <QDebug>
#include <QUrl>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void centerAndResize();
};

#endif // MAINWINDOW_H
