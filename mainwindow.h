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

signals:
    void windowClosed();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent* event);
    void centerAndResize();
    void readSettings();
    void writeSettings();
};

#endif // MAINWINDOW_H
